#ifndef BASE_MATH_MATRIX_H
#define BASE_MATH_MATRIX_H

#include "base_math_config.h"
#include "math.h"

class BASE_MATH_MATRIX
{	

public:
    BASE_MATH_MATRIX(void);

    void MatrixAdd( float* fMatrixA,float* fMatrixB,float* Result,unsigned int m,unsigned int n );  //矩阵加法
    void MatrixSub( float* fMatrixA,float* fMatrixB,float* Result,unsigned int m,unsigned int n );	//矩阵减法
    void MatrixMultiply(	float* fMatrixA,unsigned int uRowA,unsigned int uColA,
                            float* fMatrixB,unsigned int uRowB,unsigned int uColB,
                            float* MatrixResult );																									//矩阵乘法
    void MatrixTranspose(float* fMatrixA,unsigned int m,unsigned n,float* fMatrixB);							//矩阵转置

    float Matrix_Getdet(float* matrix_deal, float* matrix_copyspace,int n);												//矩阵行列式的值
    void Matrix_Inverse(float* matrix_in,float* matrix_inverse,int n);														//矩阵求逆

private:

};

extern BASE_MATH_MATRIX base_math_matrix;

#endif // #ifndef BASE_MATH_MATRIX_H

