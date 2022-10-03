#include "MatrixUtil.h"

void MatrixUtil::consistentDotMultiplication(int** matrix1, int** matrix2, int** result, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void MatrixUtil::parallelDotMultiplication(int** matrix1, int** matrix2, int** result, int N) {
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

void MatrixUtil::consistentBlockMultiplication(int** matrix1, int** matrix2, int** result, int N) {
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

void MatrixUtil::parallelBlockMultiplication(int** matrix1, int** matrix2, int** result, int N) {
    int i, j, k, jj, kk, temp;
    omp_set_num_threads(threadNum);
    int chunk = 1;
#pragma omp parallel shared(matrix1, matrix2, result) private(i, j, k, jj, kk, temp)
#pragma omp for schedule (static, chunk)
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
