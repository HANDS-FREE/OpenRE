/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: base_math_matrix.cpp
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
* chenyingbing  2017.4.16   V1.7           all of these is replaced by Eigen3... ahahhaa.
* Description:  本文件封装了基本的数学矩阵函数
*
*  Matrix_Cb2n: body frame to reference frame.
*
*  c(pitch)c(yaw)  s(pitch)s(roll)c(yaw)-c(roll)s(yaw)     s(pitch)c(roll)c(yaw)+s(roll)s(yaw)     px
*  c(pitch)s(yaw)  s(pitch)s(roll)s(yaw)+c(roll)c(yaw)     s(pitch)c(roll)s(yaw)-s(roll)c(yaw)     py
*  -s(pitch)       c(pitch)s(roll)                         c(pitch)c(roll)                         pz
*  0               0                                       0                                       1.0
*
*  qw*qw + qx*qx - qy*qy - qz*qz   2*qx*qy - 2*qw*qz               2*qx*qz + 2*qw*qy               px
*  2*qx*qy + 2*qw*qz               qw*qw - qx*qx + qy*qy - qz*qz   2*qy*qz - 2*qw*qx               py
*  2*qx*qz - 2*qw*qy               2*qy*qz + 2*qw*qx               qw*qw - qx*qx - qy*qy + qz*qz   pz
*  0                               0                               0                               1.0
*
*  c(yaw)  -s(yaw)     0     px
*  s(yaw)  c(yaw)      0     py
*  0       0           1     pz
*  0       0           0     1.0
***********************************************************************************************************************/

#include "base_math_matrix.h"

void BMATH_RMAT::fufill_Cb2n(Eigen::Quaternionf &in_q)
{
    #define qw      in_q.coeffs()[3]
    #define qx      in_q.coeffs()[0]
    #define qy      in_q.coeffs()[1]
    #define qz      in_q.coeffs()[2]

    mat.data()[0] = 1 - (qy*qy + qz*qz)*2,      mat.data()[3] = 2*qx*qy - 2*qw*qz,          mat.data()[6] = 2*qx*qz + 2*qw*qy,
     mat.data()[1] = 2*qx*qy + 2*qw*qz,         mat.data()[4] = 1 - (qx*qx + qz*qz)*2,      mat.data()[7] = 2*qy*qz - 2*qw*qx,
      mat.data()[2] = 2*qx*qz - 2*qw*qy,        mat.data()[5] = 2*qy*qz + 2*qw*qx,          mat.data()[8] = 1 - (qx*qx + qy*qy)*2;
}

void BMATH_RMAT::fufill_Cn2b(Eigen::Quaternionf &in_q)
{
    #define qw      in_q.coeffs()[3]
    #define qx      in_q.coeffs()[0]
    #define qy      in_q.coeffs()[1]
    #define qz      in_q.coeffs()[2]

    mat.data()[0] = 1 - (qy*qy + qz*qz)*2,      mat.data()[1] = 2*qx*qy - 2*qw*qz,          mat.data()[2] = 2*qx*qz + 2*qw*qy,
     mat.data()[3] = 2*qx*qy + 2*qw*qz,         mat.data()[4] = 1 - (qx*qx + qz*qz)*2,      mat.data()[5] = 2*qy*qz - 2*qw*qx,
      mat.data()[6] = 2*qx*qz - 2*qw*qy,        mat.data()[7] = 2*qy*qz + 2*qw*qx,          mat.data()[8] = 1 - (qx*qx + qy*qy)*2;
}

/// old remained function:

/*
BASE_MATH_MATRIX base_math_matrix;

BASE_MATH_MATRIX::BASE_MATH_MATRIX(void)
{
}
*/


/***********************************************************************************************************************
* Function:    void BASE_MATH_MATRIX::MatrixAdd( double *fMatrixA,double *fMatrixB,double *Result,
                                                             unsigned int m,unsigned int n )
* Scope:        public
*
* Description:	矩阵加法
                                Result = MatrixA + MatrixB    矩阵大小m×n
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
* by   chenyingbing  2015.12.1   creat
***********************************************************************************************************************/
/*
void BASE_MATH_MATRIX::MatrixAdd( float* fMatrixA,float* fMatrixB,float* Result,
                                  unsigned int m,unsigned int n )
{
    unsigned int index_i = 0;
    unsigned int index_j = 0;
    unsigned int itemp = 0;

    for (;index_i<m;index_i++)
        for (index_j=0;index_j<n;index_j++)
        {
            itemp = index_i*n+index_j;
            *(Result+itemp) = *(fMatrixA+itemp) + *(fMatrixB+itemp);
        }
} 
*/

/***********************************************************************************************************************
* Function:    void BASE_MATH_MATRIX::MatrixSub( double *fMatrixA,double *fMatrixB,double *Result,
                                                             unsigned int m,unsigned int n )
* Scope:        public
*
* Description:	矩阵减法
                                Result = MatrixA - MatrixB   矩阵大小m×n
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
* by   chenyingbing  2015.12.1   creat
***********************************************************************************************************************/
/*
void BASE_MATH_MATRIX::MatrixSub( float* fMatrixA,float* fMatrixB,float* Result,
                                  unsigned int m,unsigned int n )
{
    unsigned int index_i = 0;
    unsigned int index_j = 0;
    unsigned int itemp = 0;
    for (index_i=0;index_i<m;index_i++)
        for (index_j=0;index_j<n;index_j++)
        {
            itemp = index_i*n+index_j;
            *(Result+itemp) = *(fMatrixA+itemp) - *(fMatrixB+itemp);
        }
}	
*/

/***********************************************************************************************************************
* Function:    void BASE_MATH_MATRIX::MatrixMultiply( 	double* fMatrixA,unsigned int uRowA,unsigned int uColA,
                                                                                                                double* fMatrixB,unsigned int uRowB,unsigned int uColB,
                                                                                                                double* MatrixResult )
* Scope:        public
*
* Description:	矩阵乘法
                                Result = MatrixA * MatrixB    uRowA×uColB	uRowB×uColB
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
* by   chenyingbing  2015.12.1   creat
***********************************************************************************************************************/

/*
void BASE_MATH_MATRIX::MatrixMultiply(float* fMatrixA,unsigned int uRowA,unsigned int uColA,
                                      float* fMatrixB,unsigned int uRowB,unsigned int uColB,
                                      float* MatrixResult )
{
    unsigned int index_i = 0;
    unsigned int index_j = 0;
    unsigned int index_l = 0;
    unsigned int index_u = 0;
    unsigned int index_k = 0;
    unsigned int index_v = 0;

    if(uColA==uRowB){
        for(index_i=0;index_i<uRowA;index_i++)
            for(index_j=0;index_j<uColB;index_j++)
            {
                index_u = index_i*uColB + index_j;
                MatrixResult[index_u] = 0.0;
                for(index_l=0;index_l<uColA;index_l++)
                {
                    index_k = index_i*uColA+index_l;
                    index_v = index_l*uColB+index_j;

                    if ((((fMatrixA[index_k]))!=0.0f) && (((fMatrixB[index_v]))!=0.0f))
                        (MatrixResult[index_u]) += ((fMatrixA[index_k])) * ((fMatrixB[index_v]));

                }
            }
    }
}
*/

/***********************************************************************************************************************
* Function:    void BASE_MATH_MATRIX::MatrixTranspose(double* fMatrixA,unsigned int m,unsigned n,double* fMatrixB)
*
* Scope:        public
*
* Description:	转置
                                fMatrixB = MatrixA'  m×n
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
* by   chenyingbing  2015.12.1   creat
***********************************************************************************************************************/

/*
void BASE_MATH_MATRIX::MatrixTranspose(float* fMatrixA,unsigned int m,unsigned n,float* fMatrixB)
{
    unsigned int index_i = 0;
    unsigned int index_j = 0;
    unsigned int index_u = 0;
    unsigned int index_v = 0;

    for (index_i=0;index_i<m;index_i++)
        for (index_j=0;index_j<n;index_j++)
        {
            index_u = index_j*m+index_i;
            index_v = index_i*n+index_j;
            fMatrixB[index_u] = fMatrixA[index_v];
        }
}
*/

/***********************************************************************************************************************
* Function:     double BASE_MATH_MATRIX::Matrix_Getdet(double *matrix_calculate, double *matrix_copyspace,int n)
*
* Scope:        public
*
* Description:	矩阵的行列式的值
                                摘自网上：因为会改变输入矩阵的值，所以需要用户提供一个足够空间的“矩阵” 用于复制，保证输入矩阵不改变值。
                                全选主元高斯消去法 n×n 用于计算的matrix_calculate 和 同等空间大小的 matrix_copyspace
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
* by   chenyingbing  2015.12.1   creat
***********************************************************************************************************************/

/*
float BASE_MATH_MATRIX::Matrix_Getdet(float* matrix_calculate, float* matrix_copyspace,int n)
{
    int i,j,k,is,js,l,u,v;
    float f,q,d;
    float det;
    f=1.0; det=1.0;

    // copy
    for(i=0;i<(n*n);i++)
    {
        matrix_copyspace[i] = matrix_calculate[i];
    }

    // caculate
    for (k=0; k<=n-2; k++)
    {
        q=0.0;
        for (i=k; i<=n-1; i++)
            for (j=k; j<=n-1; j++)
            {
                l=i*n+j; d=fabs(matrix_copyspace[l]);
                if (d>q)
                {
                    q=d;
                    is=i;
                    js=j;
                }
            }
        if (q+1.0f==1.0f)
        {
            det=0.0;

        }
        if (is!=k)
        {
            f=-f;
            for (j=k; j<=n-1; j++)
            {
                u=k*n+j; v=is*n+j;
                d=matrix_copyspace[u]; matrix_copyspace[u]=matrix_copyspace[v]; matrix_copyspace[v]=d;
            }
        }
        if (js!=k)
        {
            f=-f;
            for (i=k; i<=n-1; i++)
            {
                u=i*n+js; v=i*n+k;
                d=matrix_copyspace[u]; matrix_copyspace[u]=matrix_copyspace[v]; matrix_copyspace[v]=d;
            }
        }
        l=k*n+k;
        det=det*matrix_copyspace[l];
        for (i=k+1; i<=n-1; i++)
        {
            d=matrix_copyspace[i*n+k]/matrix_copyspace[l];
            for (j=k+1; j<=n-1; j++)
            {
                u=i*n+j;
                matrix_copyspace[u]=matrix_copyspace[u]-d*matrix_copyspace[k*n+j];
            }
        }
    }
    det=f*det*matrix_copyspace[n*n-1];

    return det;
} 
*/

/***********************************************************************************************************************
* Function:     void BASE_MATH_MATRIX::Matrix_Inverse(double *matrix_in,double *matrix_inverse,int n)
*
* Scope:        public
*
* Description:	矩阵的行列式的逆   n×n 用于计算的：	matrix_in  返回值：					matrix_inverse
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
* by   chenyingbing  2015.12.1   creat
***********************************************************************************************************************/
/*
void BASE_MATH_MATRIX::Matrix_Inverse(float* matrix_in,float* matrix_inverse,int n)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int u = 0;
    int v = 0;
    int temp_row[10],temp_col[10];
    int * prow = temp_row,urow = 0;		  //找到的最大值的行数
    int * pcol = temp_col,ucol = 0;			//找到的最大值的列数
    float ftemp_max = 0.0;
    float ftemp = 0.0;

    //copy
    for(i=0;i<(n*n);i++){
        matrix_inverse[i] = matrix_in[i];
    }

    //caculate
    for (i=0;i<10;i++)
    {
        temp_row[i] = 0;
        temp_col[i] = 0;
    }

    for (k=0;k<n;k++)
    {
        ftemp_max =0.0;		 //找到剩余矩阵项中的最大值
        for (i=k;i<n;i++)
            for (j=k;j<n;j++)
            {
                l = i*n+j;
                ftemp = fabs(*(matrix_inverse+l));
                if (ftemp_max<ftemp)
                {
                    ftemp_max = ftemp;
                    *(prow+k) = urow = i;
                    *(pcol+k) = ucol= j;
                }
            }


        if (urow!=k)			  //如果当前行不包含最大值换行
        {
            for (j=0;j<n;j++)
            {
                u = k*n +j;
                v = urow*n+j;
                ftemp = *(matrix_inverse+u);
                *(matrix_inverse+u) = *(matrix_inverse+v);
                *(matrix_inverse+v) = ftemp;
            }
        }

        if (ucol!=k)			//如果当前列不包含最大值换列
        {
            for (i=0;i<n;i++)
            {
                u = i*n+k;
                v = i*n+ucol;
                ftemp = *(matrix_inverse+u);
                *(matrix_inverse+u) = *(matrix_inverse+v);
                *(matrix_inverse+v) = ftemp;
            }
        }

        l = k*n+k;
        ftemp = *(matrix_inverse+l) = 1.0f/(*(matrix_inverse+l));

        for (j=0;j<n;j++)
        {
            if (j!=k)
            {
                u = k*n+j;
                *(matrix_inverse+u) *= *(matrix_inverse+l);
            }
        }

        for (i=0;i<n;i++)	  //还不知道为什么
        {
            if (i!=k)
            {
                for (j=0;j<n;j++)
                {
                    if (j!=k)
                    {
                        u = i*n+j;
                        *(matrix_inverse+u) -= (*(matrix_inverse+i*n+k))*(*(matrix_inverse+k*n+j));
                    }
                }
            }
        }

        for (i=0;i<n;i++)
        {
            if (i!=k)
            {
                u = i*n+k;
                *(matrix_inverse+u) = -(*(matrix_inverse+u))*(*(matrix_inverse+l));
            }
        }
    }

    for (k=n-1;k>=0;k--)
    {
        if ((*(pcol+k))!=k)
        {
            for (j=0;j<n;j++)
            {
                u = k*n+j;
                v = (*(pcol+k))*n+j;
                ftemp = *(matrix_inverse+u);
                *(matrix_inverse+u) = *(matrix_inverse+v);
                *(matrix_inverse+v) = ftemp;
            }
        }

        if ((*(prow+k))!=k)
        {
            for (i=0;i<n;i++)
            {
                u = i*n+k;
                v = i*n+(*(prow+k));
                ftemp = *(matrix_inverse+u);
                *(matrix_inverse+u) = *(matrix_inverse+v);
                *(matrix_inverse+v) = ftemp;
            }
        }
    }
}
*/
