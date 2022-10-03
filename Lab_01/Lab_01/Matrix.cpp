#include "Matrix.h"

void Matrix::parallelBlockMultiplication(int** matrix1, int** matrix2, int** result, int N, int threadNum, int blockSize, int loopNum)
{
    int i, j, k, jj, kk, temp;
    omp_set_dynamic(0);
    omp_set_num_threads(threadNum);
    int chunk = 1;
    int q = N / blockSize;
//#pragma omp parallel shared(matrix1, matrix2, result) private(i, j, k, jj, kk, temp)
#pragma omp parallel for if (loopNum == 1)
//#pragma omp for schedule (static, 2)
    for (int ii = 0; ii < q; ii++) {
#pragma omp parallel for if (loopNum == 2)
        for (int jj = 0; jj < q; jj++) {
            for (int kk = 0; kk < q; kk++) {
                for (int i = 0; i < blockSize; i++) {
                    for (int j = 0; j < blockSize; j++) {
                        for (int k = 0; k < blockSize; k++) {
                            int i_res = ii * blockSize + i;
                            int j_res = jj * blockSize + j;
                            int k_res = kk * blockSize + k;
                            result[i_res][j_res] += matrix1[i_res][k_res] * matrix2[k_res][j_res];
                        }
                    }
                    /*temp = 0;
                    for (int k = kk; k < ((kk + blockSize) > N ? N : (kk + blockSize)); k++) {
                        temp += matrix1[i][k] * matrix2[k][j];
                    }
                    result[i][j] += temp;*/
                }
            }
        }
    }
}

void Matrix::consistentBlockMultiplication(int** matrix1, int** matrix2, int** result, int N, int blockSize)
{
    int temp;
    for (int jj = 0; jj < N; jj += blockSize) {
        for (int kk = 0; kk < N; kk += blockSize) {
            for (int i = 0; i < N; i++) {
                for (int j = jj; j < ((jj + blockSize) > N ? N : (jj + blockSize)); j++) {
                    temp = 0;
                    for (int k = kk; k < ((kk + blockSize) > N ? N : (kk + blockSize)); k++) {
                        temp += matrix1[i][k] * matrix2[k][j];
                    }
                    result[i][j] += temp;
                }
            }
        }
    }
}

void Matrix::parallelDotMultiplication(int** matrix1, int** matrix2, int** result, int N, int threadNum, int loopNum)
{
    omp_set_num_threads(threadNum);
    int i, j, k;
#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[i][j] = 0;
            for (k = 0; k < N; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void Matrix::consistentDotMultiplication(int** matrix1, int** matrix2, int** result, int N)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}
