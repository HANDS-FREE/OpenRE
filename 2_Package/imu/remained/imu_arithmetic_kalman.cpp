/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_arithmetic_kalman.h
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* chenyingbing  2015.12.1   V1.6           creat this file
* Description:  本文件定义了kalman滤波的代码
*
***********************************************************************************************************************/

#include "imu_arithmetic_kalman.h"

KALMAN	kalman_filter1;

KALMAN::KALMAN()
{
    Pk_k[0] = 0.1f;  	Pk_k[1] = 0;		Pk_k[2] = 0;			Pk_k[3] = 0;
    Pk_k[4] = 0;		Pk_k[5] = 0.1f;	    Pk_k[6] = 0;			Pk_k[7] = 0;
    Pk_k[8] = 0;		Pk_k[9] = 0;		Pk_k[10] = 0.1f;	    Pk_k[11] = 0;
    Pk_k[12] = 0;		Pk_k[13] = 0;		Pk_k[14] = 0;			Pk_k[15] = 0.1f;
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                 以下是 内部计算函数                                              				     ***
***                                                                                                                  ***
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:   	void KALMAN::Kalman_Pk_pre(double *F_Jacobian,double *Pre_Cov)
*
* Scope:        private
*
* Description:  卡尔曼 协方差矩阵预测   	 F矩阵，Q(t)：预测过程协方差矩阵
*								Pk_pre = F(t)P(t) + P(t)F(t)^T + Q(t)
*								4×4				4×4					4×4				 4×4
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f4 -- 85us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void KALMAN::Kalman_Pk_pre(IPType *F_Jacobian,IPType *Pre_Cov)
{
    //double *Pk_pre
    static IPType dealMatrix1[16];	//4×4
    static IPType dealMatrix2[16];	//4×4
    static IPType dealMatrix3[16];	//4×4

    //F(t)P(t) > dealMatrix1
    base_math_matrix.MatrixMultiply(F_Jacobian,4,4,Pk_k,4,4,dealMatrix1 );
    //F(t)^T	 > dealMatrix2
    base_math_matrix.MatrixTranspose(F_Jacobian,4,4,dealMatrix2);
    //P(t)F(t)^T > dealMatrix3
    base_math_matrix.MatrixMultiply(Pk_k,4,4,dealMatrix2,4,4,dealMatrix3);

    //F(t)P(t) + P(t)F(t)^T > dealMatrix2
    base_math_matrix.MatrixAdd(dealMatrix1,dealMatrix3,dealMatrix2, 4, 4);

    //F(t)P(t) + P(t)F(t)^T + Q(t) > Pk_pre
    base_math_matrix.MatrixAdd(dealMatrix2,Pre_Cov,Pk_pre, 4, 4);

}

/***********************************************************************************************************************
* Function:   	void KALMAN::Kalman_Kk(double *H_Jacobian,double *Mes_Cov)
*
* Scope:        private
*
* Description:  卡尔曼 K增益矩阵  H矩阵，R(t)：测量过程协方差矩阵
*								Kk = Pk|k-1*Hk^T * (Hk*Pk|k-1*Hk^T+Rk)^-1
*								4×3		 4×4  4*3					 	3*3
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f4 -- 144us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void KALMAN::Kalman_Kk(IPType *H_Jacobian,IPType *Mes_Cov)
{
    //double *Kk
    static IPType dealMatrix0[16];
    static IPType dealMatrix1[16];
    static IPType dealMatrix2[16];

    //Hk^T > dealMatrix1 4×3
    base_math_matrix.MatrixTranspose(H_Jacobian,3,4,dealMatrix1);
    //Pk|k-1*Hk^T > dealMatrix0 4×3 定
    base_math_matrix.MatrixMultiply(Pk_pre,4,4,dealMatrix1,4,3,dealMatrix0);

    //Hk * Pk|k-1*Hk^T > dealMatrix2 3×3
    base_math_matrix.MatrixMultiply(H_Jacobian,3,4,dealMatrix0,4,3,dealMatrix2);

    //Hk*Pk|k-1*Hk^T + Rk > dealMatrix1 3×3
    base_math_matrix.MatrixAdd(dealMatrix2,Mes_Cov,dealMatrix1, 3, 3);

    //(Hk*Pk|k-1*Hk^T+Rk)^-1 > dealMatrix2 3×3
    base_math_matrix.Matrix_Inverse(dealMatrix1,dealMatrix2,3);

    //Pk|k-1*Hk^T * (Hk*Pk|k-1*Hk^T+Rk)^-1 > Kk 4×3
    base_math_matrix.MatrixMultiply(dealMatrix0,4,3,dealMatrix2,3,3,Kk);
}

/***********************************************************************************************************************
* Function:   	void KALMAN::Kalman_Xfusion(double *X_Fus, double *X_Mes, double *X_PRE, double *Kk)
*
* Scope:        private
*
* Description:  卡尔曼融合XSTATE
*								Xk|k = Xk|k-1 + Kk(zk - h(Xk|k-1))
*								4×1		 4×1      4×3(3×1 - 3×1)
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f4 -- 24us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void KALMAN::Kalman_Xfusion(IPType *X_Fusion, IPType *X_PRE, IPType *Z_Mes, IPType *Z_pre)
{
    static IPType dealMatrix0[4];
    static IPType dealMatrix1[4];

    //zk - h(Xk|k-1) > dealMatrix0 3×1
    dealMatrix0[0] = Z_Mes[0] - Z_pre[0];
    dealMatrix0[1] = Z_Mes[1] - Z_pre[1];
    dealMatrix0[2] = Z_Mes[2] - Z_pre[2];

    //Kk(zk - h(Xk|k-1)) > dealMatrix1 4×1
    base_math_matrix.MatrixMultiply(Kk,4,3,dealMatrix0,3,1,dealMatrix1);

    //Xk|k-1 + Kk(zk - h(Xk|k-1)) > X_Fusion 4×1
    X_Fusion[0] = X_PRE[0] + dealMatrix1[0];
    X_Fusion[1] = X_PRE[1] + dealMatrix1[1];
    X_Fusion[2] = X_PRE[2] + dealMatrix1[2];
    X_Fusion[3] = X_PRE[3] + dealMatrix1[3];

}


/***********************************************************************************************************************
* Function:   	void KALMAN::Kalman_Pk(double *H_Jacobian)
*
* Scope:        private
*
* Description:  卡尔曼 递归Pkk
*								Pk|k = (I  - Kk * Hk)* Pk|k-1
*								4×4		  4×4  4×3  3×4	 4×4
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f4 -- 57us(fpu)
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void KALMAN::Kalman_Pk(IPType *H_Jacobian)
{
    //未验证
    static IPType I_Matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    static IPType dealMatrix0[16];
    static IPType dealMatrix1[16];

    //Kk * Hk > dealMatrix0 4×4
    base_math_matrix.MatrixMultiply(Kk,4,3,H_Jacobian,3,4,dealMatrix0);

    //(I  - Kk * Hk) > dealMatrix1 4×4
    base_math_matrix.MatrixSub(I_Matrix,dealMatrix0,dealMatrix1,4,4);

    //(I  - Kk * Hk)* Pk|k-1 > Pk_k
    base_math_matrix.MatrixMultiply(dealMatrix1,4,4,Pk_pre,4,4,Pk_k);

}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                 以下是 接口函数                                              						 ***
***                                                                                                                  ***
***********************************************************************************************************************/
/***********************************************************************************************************************
void KALMAN::Kalman_Update(IPType *F_Jacobian, 		IPType *H_Jacobian,
                           IPType *Pre_Cov, 			IPType *Mes_Cov,
                           IPType *Z_Mes, 			IPType *Z_pre,
                           IPType *X_PRE, 		IPType *X_Fusion_Return)
*
* Scope:        pubilc
*
* Description:  扩展卡尔曼全过程：
*
*
* Arguments:
*
* Return:
*
* Cpu_Time:     stm32f4 -- 125us(fpu)[matrix] -> 50us(fpu)[optimize]
*
* History:
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void KALMAN::Kalman_Update(IPType *F_Jacobian, 		IPType *H_Jacobian,
                           IPType *Pre_Cov, 			IPType *Mes_Cov,
                           IPType *Z_Mes, 			IPType *Z_pre,
                           IPType *X_PRE, 		IPType *X_Fusion_Return)
{
#define a0		matrixA[0]
#define a1		matrixA[1]
#define a2		matrixA[2]
#define a3		matrixA[3]
#define a4		matrixA[4]
#define a5		matrixA[5]
#define a6		matrixA[6]
#define a7		matrixA[7]
#define a8		matrixA[8]
#define a9		matrixA[9]
#define a10		matrixA[10]
#define a11		matrixA[11]
#define a12		matrixA[12]
#define a13		matrixA[13]
#define a14		matrixA[14]
#define a15		matrixA[15]

#define b0		matrixB[0]
#define b1		matrixB[1]
#define b2		matrixB[2]
#define b3		matrixB[3]
#define b4		matrixB[4]
#define b5		matrixB[5]
#define b6		matrixB[6]
#define b7		matrixB[7]
#define b8		matrixB[8]
#define b9		matrixB[9]
#define b10		matrixB[10]
#define b11		matrixB[11]
#define b12		matrixB[12]
#define b13		matrixB[13]
#define b14		matrixB[14]
#define b15		matrixB[15]

#define c0		matrixC[0]
#define c1		matrixC[1]
#define c2		matrixC[2]
#define c3		matrixC[3]
#define c4		matrixC[4]
#define c5		matrixC[5]
#define c6		matrixC[6]
#define c7		matrixC[7]
#define c8		matrixC[8]
#define c9		matrixC[9]
#define c10		matrixC[10]
#define c11		matrixC[11]

#define d0		matrixD[0]
#define d1		matrixD[1]
#define d2		matrixD[2]
#define d3		matrixD[3]
#define d4		matrixD[4]
#define d5		matrixD[5]
#define d6		matrixD[6]
#define d7		matrixD[7]
#define d8		matrixD[8]

#define e0		matrixE[0]
#define e1		matrixE[1]
#define e2		matrixE[2]
#define e3		matrixE[3]
#define e4		matrixE[4]
#define e5		matrixE[5]
#define e6		matrixE[6]
#define e7		matrixE[7]
#define e8		matrixE[8]
#define e9		matrixE[9]
#define e10		matrixE[10]
#define e11		matrixE[11]

    static unsigned char i;

    static IPType matrixd1[16];
    static IPType matrixd2[16];

    static IPType matrixd01[9];

    static IPType matrixA[16];	//4×4
    static IPType matrixB[16];	//4×4
    static IPType matrixC[12];	//3×4
    static IPType matrixD[9];		//3×3
    static IPType matrixE[12];	//4×3

    static IPType VectorA[4];		//4×1

    static IPType matrix_deal[4];
    /******************************************************
    //矩阵计算未优化：
    //PREDICT
    Kalman_Pk_pre(F_Jacobian,Pre_Cov);
    //UPDATE
    Kalman_Kk(H_Jacobian, Mes_Cov);
  Kalman_Xfusion(X_Fusion_Return, X_PRE, Z_Mes, Z_pre);
    Kalman_Pk(H_Jacobian);
    ******************************************************/

    //Kalman_Pk_pre(F_Jacobian,Pre_Cov)
    //4×4				4×4					4×4				 4×4

    //>> matrixd1:F(t)P(t)
    for(i=0;i<16;i++){
        matrixA[i] = F_Jacobian[i];
        matrixB[i] = Pk_k[i];
    }
    matrixd1[0] = a0*b0 + a1*b4 + a2*b8 + a3*b12;
    matrixd1[1] = a0*b1 + a1*b5 + a2*b9 + a3*b13;
    matrixd1[2] = a0*b2 + a1*b6 + a2*b10 + a3*b14;
    matrixd1[3] = a0*b3 + a1*b7 + a2*b11 + a3*b15;
    matrixd1[4] =  a4*b0 + a5*b4 + a6*b8 + a7*b12;
    matrixd1[5] = a4*b1 + a5*b5 + a6*b9 + a7*b13;
    matrixd1[6] = a4*b2 + a5*b6 + a6*b10 + a7*b14;
    matrixd1[7] = a4*b3 + a5*b7 + a6*b11 + a7*b15;
    matrixd1[8] = a8*b0 + a9*b4 + a10*b8 + a11*b12;
    matrixd1[9] = a8*b1 + a9*b5 + a10*b9 + a11*b13;
    matrixd1[10] = a8*b2 + a9*b6 + a10*b10 + a11*b14;
    matrixd1[11] = a8*b3 + a9*b7 + a10*b11 + a11*b15;
    matrixd1[12] = a12*b0 + a13*b4 + a14*b8 + a15*b12;
    matrixd1[13] = a12*b1 + a13*b5 + a14*b9 + a15*b13;
    matrixd1[14] = a12*b2 + a13*b6 + a14*b10 + a15*b14;
    matrixd1[15] = a12*b3 + a13*b7 + a14*b11 + a15*b15;

    //>> matrixd2:P(t)F(t)^T
    //for(i=0;i<16;i++){
    //	matrixA[i] = F_Jacobian[i];
    // 	matrixB[i] = Pk_k[i];
    //} 上面已经赋值
    matrixd2[0] = a0*b0 + a1*b1 + a2*b2 + a3*b3;
    matrixd2[1] = a4*b0 + a5*b1 + a6*b2 + a7*b3;
    matrixd2[2] = a8*b0 + a9*b1 + a10*b2 + a11*b3;
    matrixd2[3] = a12*b0 + a13*b1 + a14*b2 + a15*b3;
    matrixd2[4] =  a0*b4 + a1*b5 + a2*b6 + a3*b7;
    matrixd2[5] = a4*b4 + a5*b5 + a6*b6 + a7*b7;
    matrixd2[6] = a8*b4 + a9*b5 + a10*b6 + a11*b7;
    matrixd2[7] = a12*b4 + a13*b5 + a14*b6 + a15*b7;
    matrixd2[8] = a0*b8 + a1*b9 + a2*b10 + a3*b11;
    matrixd2[9] = a4*b8 + a5*b9 + a6*b10 + a7*b11;
    matrixd2[10] = a8*b8 + a9*b9 + a10*b10 + a11*b11;
    matrixd2[11] = a12*b8 + a13*b9 + a14*b10 + a15*b11;
    matrixd2[12] = a0*b12 + a1*b13 + a2*b14 + a3*b15;
    matrixd2[13] = a4*b12 + a5*b13 + a6*b14 + a7*b15;
    matrixd2[14] = a8*b12 + a9*b13 + a10*b14 + a11*b15;
    matrixd2[15] = a12*b12 + a13*b13 + a14*b14 + a15*b15;

    //>> Pk_pre:F(t)P(t) + P(t)F(t)^T + Q(t)
    for(i=0;i<16;i++){
        Pk_pre[i] = matrixd1[i] + matrixd2[i] + Pre_Cov[i];
    }

    //Kalman_Kk(H_Jacobian, Mes_Cov);
    //Kk = Pk|k-1*Hk^T * (Hk*Pk|k-1*Hk^T+Rk)^-1
    //4×3		 4×4  4*3			3×4  4×4  4×3  3×3

    //>> matrixd01:Hk*Pk|k-1*Hk^T +Rk
    for(i=0;i<12;i++){
        matrixC[i] = H_Jacobian[i];
        matrixB[i] = Pk_pre[i];
    }
    matrixB[12] = Pk_pre[12];
    matrixB[13] = Pk_pre[13];
    matrixB[14] = Pk_pre[14];
    matrixB[15] = Pk_pre[15];

    matrix_deal[0] = (b0*c0 + b4*c1 + b8*c2 + b12*c3);
    matrix_deal[1] = (b1*c0 + b5*c1 + b9*c2 + b13*c3);
    matrix_deal[2] = (b2*c0 + b6*c1 + b10*c2 + b14*c3);
    matrix_deal[3] = (b3*c0 + b7*c1 + b11*c2 + b15*c3);

    matrixd01[0] = c0*matrix_deal[0] + c1*matrix_deal[1] + c2*matrix_deal[2] + c3*matrix_deal[3];
    matrixd01[0] += Mes_Cov[0];

    matrixd01[1] = c4*matrix_deal[0] + c5*matrix_deal[1] + c6*matrix_deal[2] + c7*matrix_deal[3];
    matrixd01[1] += Mes_Cov[1];

    matrixd01[2] = c8*matrix_deal[0] + c9*matrix_deal[1] + c10*matrix_deal[2] + c11*matrix_deal[3];
    matrixd01[2] += Mes_Cov[2];

    matrix_deal[0] = (b0*c4 + b4*c5 + b8*c6 + b12*c7);
    matrix_deal[1] = (b1*c4 + b5*c5 + b9*c6 + b13*c7);
    matrix_deal[2] = (b2*c4 + b6*c5 + b10*c6 + b14*c7);
    matrix_deal[3] = (b3*c4 + b7*c5 + b11*c6 + b15*c7);

    matrixd01[3] = c0*matrix_deal[0] + c1*matrix_deal[1] + c2*matrix_deal[2] + c3*matrix_deal[3];
    matrixd01[3] += Mes_Cov[3];

    matrixd01[4] = c4*matrix_deal[0] + c5*matrix_deal[1] + c6*matrix_deal[2] + c7*matrix_deal[3];
    matrixd01[4] += Mes_Cov[4];

    matrixd01[5] = c8*matrix_deal[0] + c9*matrix_deal[1] + c10*matrix_deal[2] + c11*matrix_deal[3];
    matrixd01[5] += Mes_Cov[5];

    matrix_deal[0] = (b0*c8 + b4*c9 + b8*c10 + b12*c11);
    matrix_deal[1] = (b1*c8 + b5*c9 + b9*c10 + b13*c11);
    matrix_deal[2] = (b2*c8 + b6*c9 + b10*c10 + b14*c11);
    matrix_deal[3] = (b3*c8 + b7*c9 + b11*c10 + b15*c11);

    matrixd01[6] = c0*matrix_deal[0] + c1*matrix_deal[1] + c2*matrix_deal[2] + c3*matrix_deal[3];
    matrixd01[6] += Mes_Cov[6];

    matrixd01[7] = c4*matrix_deal[0] + c5*matrix_deal[1] + c6*matrix_deal[2] + c7*matrix_deal[3];
    matrixd01[7] += Mes_Cov[7];

    matrixd01[8] = c8*matrix_deal[0] + c9*matrix_deal[1] + c10*matrix_deal[2] + c11*matrix_deal[3];
    matrixd01[8] += Mes_Cov[8];

    //>> Kk:Pk|k-1*Hk^T * (Hk*Pk|k-1*Hk^T+Rk)^-1
    //for(i=0;i<12;i++){
    //matrixC[i] = H_Jacobian[i];
    //matrixB[i] = Pk_pre[i];
    //}
    //matrixB[12] = Pk_pre[12];
    //matrixB[13] = Pk_pre[13];
    //matrixB[14] = Pk_pre[14];
    //matrixB[15] = Pk_pre[15];
    //上面已经赋值
    for(i=0;i<9;i++){
        matrixD[i] = matrixd01[i];
    }
    matrix_deal[0] = (d0*d4*d8 - d0*d5*d7 - d1*d3*d8 + d1*d5*d6 + d2*d3*d7 - d2*d4*d6);

    matrix_deal[1] = (b0*c8 + b1*c9 + b2*c10 + b3*c11);
    matrix_deal[2] = (b0*c0 + b1*c1 + b2*c2 + b3*c3);
    matrix_deal[3] = (b0*c4 + b1*c5 + b2*c6 + b3*c7);
    Kk[0] = ((d4*d8 - d5*d7)*	matrix_deal[2])/matrix_deal[0] - ((d3*d8 - d5*d6)*matrix_deal[3])/matrix_deal[0]
            + ((d3*d7 - d4*d6)*matrix_deal[1])/matrix_deal[0];
    Kk[1] = ((d0*d8 - d2*d6)* matrix_deal[3])/matrix_deal[0] - ((d1*d8 - d2*d7)*matrix_deal[2])/matrix_deal[0]
            - ((d0*d7 - d1*d6)*matrix_deal[1])/matrix_deal[0];
    Kk[2] = ((d1*d5 - d2*d4)*	matrix_deal[2])/matrix_deal[0] - ((d0*d5 - d2*d3)*matrix_deal[3])/matrix_deal[0]
            + ((d0*d4 - d1*d3)*matrix_deal[1])/matrix_deal[0];

    matrix_deal[1] = (b4*c8 + b5*c9 + b6*c10 + b7*c11);
    matrix_deal[2] = (b4*c0 + b5*c1 + b6*c2 + b7*c3);
    matrix_deal[3] = (b4*c4 + b5*c5 + b6*c6 + b7*c7);
    Kk[3] = ((d4*d8 - d5*d7)*matrix_deal[2])/matrix_deal[0] - ((d3*d8 - d5*d6)*matrix_deal[3])/matrix_deal[0]
            + ((d3*d7 - d4*d6)*matrix_deal[1])/matrix_deal[0];
    Kk[4] = ((d0*d8 - d2*d6)*matrix_deal[3])/matrix_deal[0] - ((d1*d8 - d2*d7)*matrix_deal[2])/matrix_deal[0]
            - ((d0*d7 - d1*d6)*matrix_deal[1])/matrix_deal[0];
    Kk[5] = ((d1*d5 - d2*d4)*matrix_deal[2])/matrix_deal[0] - ((d0*d5 - d2*d3)*matrix_deal[3])/matrix_deal[0]
            + ((d0*d4 - d1*d3)*matrix_deal[1])/matrix_deal[0];

    matrix_deal[1] = (b8*c8 + b9*c9 + b10*c10 + b11*c11);
    matrix_deal[2] = (b8*c0 + b9*c1 + b10*c2 + b11*c3);
    matrix_deal[3] = (b8*c4 + b9*c5 + b10*c6 + b11*c7);
    Kk[6] = ((d4*d8 - d5*d7)*matrix_deal[2])/matrix_deal[0] - ((d3*d8 - d5*d6)*matrix_deal[3])/matrix_deal[0]
            + ((d3*d7 - d4*d6)*matrix_deal[1])/matrix_deal[0];
    Kk[7] = ((d0*d8 - d2*d6)*matrix_deal[3])/matrix_deal[0] - ((d1*d8 - d2*d7)*matrix_deal[2])/matrix_deal[0]
            - ((d0*d7 - d1*d6)*matrix_deal[1])/matrix_deal[0];
    Kk[8] = ((d1*d5 - d2*d4)*matrix_deal[2])/matrix_deal[0] - ((d0*d5 - d2*d3)*matrix_deal[3])/matrix_deal[0]
            + ((d0*d4 - d1*d3)*matrix_deal[1])/matrix_deal[0];

    matrix_deal[1] = (b12*c8 + b13*c9 + b14*c10 + b15*c11);
    matrix_deal[2] = (b12*c0 + b13*c1 + b14*c2 + b15*c3);
    matrix_deal[3] = (b12*c4 + b13*c5 + b14*c6 + b15*c7);
    Kk[9] = ((d4*d8 - d5*d7)*matrix_deal[2])/matrix_deal[0] - ((d3*d8 - d5*d6)*matrix_deal[3])/matrix_deal[0]
            + ((d3*d7 - d4*d6)*matrix_deal[1])/matrix_deal[0];
    Kk[10]= ((d0*d8 - d2*d6)*matrix_deal[3])/matrix_deal[0] - ((d1*d8 - d2*d7)*matrix_deal[2])/matrix_deal[0]
            - ((d0*d7 - d1*d6)*matrix_deal[1])/matrix_deal[0];
    Kk[11]= ((d1*d5 - d2*d4)*matrix_deal[2])/matrix_deal[0] - ((d0*d5 - d2*d3)*matrix_deal[3])/matrix_deal[0]
            + ((d0*d4 - d1*d3)*matrix_deal[1])/matrix_deal[0];


    //Kalman_Xfusion(X_Fusion_Return, X_PRE, Z_Mes, Z_pre)
    //Xk|k = Xk|k-1 + Kk(zk - h(Xk|k-1))
    //4×1		 4×1      4×3(3×1 - 3×1)
    matrix_deal[0] = Z_Mes[0] - Z_pre[0];
    matrix_deal[1] = Z_Mes[1] - Z_pre[1];
    matrix_deal[2] = Z_Mes[2] - Z_pre[2];

    VectorA[0] = Kk[0]*matrix_deal[0] + Kk[1]*matrix_deal[1] + Kk[2]*matrix_deal[2];
    VectorA[1] = Kk[3]*matrix_deal[0] + Kk[4]*matrix_deal[1] + Kk[5]*matrix_deal[2];
    VectorA[2] = Kk[6]*matrix_deal[0] + Kk[7]*matrix_deal[1] + Kk[8]*matrix_deal[2];
    VectorA[3] = Kk[9]*matrix_deal[0] + Kk[10]*matrix_deal[1] + Kk[11]*matrix_deal[2];

    X_Fusion_Return[0] = X_PRE[0] + VectorA[0];
    X_Fusion_Return[1] = X_PRE[1] + VectorA[1];
    X_Fusion_Return[2] = X_PRE[2] + VectorA[2];
    X_Fusion_Return[3] = X_PRE[3] + VectorA[3];

    //Kalman_Pk(H_Jacobian)
    //Pk|k = (I  - Kk * Hk)* Pk|k-1
    //4×4		  4×4  4×3  3×4	 4×4
    for(i=0;i<12;i++){
        matrixE[i] = Kk[i];
        matrixC[i] = H_Jacobian[i];
        matrixB[i] = Pk_pre[i];
    }
    matrixB[12] = Pk_pre[12];
    matrixB[13] = Pk_pre[13];
    matrixB[14] = Pk_pre[14];
    matrixB[15] = Pk_pre[15];

    matrix_deal[0] = (c0*e0 + c4*e1 + c8*e2 - 1);
    matrix_deal[1] = (c1*e0 + c5*e1 + c9*e2);
    matrix_deal[2] = (c2*e0 + c6*e1 + c10*e2);
    matrix_deal[3] = (c3*e0 + c7*e1 + c11*e2);

    Pk_k[0] = - b0*matrix_deal[0] - b4*matrix_deal[1] - b8*matrix_deal[2] - b12*matrix_deal[3];
    Pk_k[1] = - b1*matrix_deal[0] - b5*matrix_deal[1] - b9*matrix_deal[2] - b13*matrix_deal[3];
    Pk_k[2] = - b2*matrix_deal[0] - b6*matrix_deal[1] - b10*matrix_deal[2] - b14*matrix_deal[3];
    Pk_k[3] = - b3*matrix_deal[0] - b7*matrix_deal[1] - b11*matrix_deal[2] - b15*matrix_deal[3];

}

