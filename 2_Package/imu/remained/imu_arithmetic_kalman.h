#ifndef __imu_arithmetic_kalman_H__
#define __imu_arithmetic_kalman_H__

#include "imu_config.h"

class KALMAN
{	

public:
    KALMAN(void);
    void Kalman_Update(IPType *F_Jacobian, 		IPType *H_Jacobian,
                       IPType *Pre_Cov, 		IPType *Mes_Cov,
                       IPType *Z_Mes, 		IPType *Z_pre,
                       IPType *X_PRE, 	IPType *X_Fusion_Return);

private:
    IPType Pk_k[16];			//协方差矩阵			4×4
    IPType Pk_pre[16];		//协方差矩阵预测	4×4
    IPType Kk[12];				//卡尔曼增益			4×3

    //PREDICT
    void Kalman_Pk_pre(IPType *F_Jacobian,IPType *Pre_Cov);
    //UPDATE
    void Kalman_Kk(IPType *H_Jacobian, IPType *Mes_Cov);
    void Kalman_Xfusion(IPType *X_Fusion, IPType *X_PRE, IPType *Z_Mes, IPType *Z_pre);
    void Kalman_Pk(IPType *H_Jacobian);

};

extern KALMAN	kalman_filter1;


#endif
