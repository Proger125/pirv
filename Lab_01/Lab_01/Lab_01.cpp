#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <ctime>
#include <fstream>
#include <vector>
#include "Matrix.h"

int threadNum = 8;

using namespace std;

void randomiseMatrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 200 - 100;
        }
    }
}

//void printMatrix(int** matrix) {
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            cout << matrix[i][j] << " ";
//        }
//        cout << endl;
//    }
//}

void makeZeroMatrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 0;
        }
    }
}

int main(int argc, char** argv){
    srand(time(NULL));
    int** matrix1;
    int** matrix2;
    int** result;
    unsigned int start;
    unsigned int end;
    int* sizes = (int*)malloc(sizeof(int) * 4);
    sizes[0] = 100;
    sizes[1] = 500;
    sizes[2] = 1000;
    sizes[3] = 1500;
    int* blockSizes = (int*)malloc(sizeof(int) * 5);
    blockSizes[0] = 1;
    blockSizes[1] = 10;
    blockSizes[2] = 50;
    blockSizes[3] = 100;
    blockSizes[4] = 500;
    vector<int> consistentDotResults(4);
    vector<int> parallelDotResults(4);
    ofstream fout("output.txt");
    for (int i = 0; i < 4; i++) {
        fout << sizes[i] << endl;
        matrix1 = (int**)malloc(sizeof(int*) * sizes[i]);
        matrix2 = (int**)malloc(sizeof(int*) * sizes[i]);
        result = (int**)malloc(sizeof(int*) * sizes[i]);
        for (int k = 0; k < sizes[i]; k++) {
            matrix1[k] = (int*)malloc(sizeof(int) * sizes[i]);
            matrix2[k] = (int*)malloc(sizeof(int) * sizes[i]);
            result[k] = (int*)malloc(sizeof(int) * sizes[i]);
        }
        randomiseMatrix(matrix1, sizes[i]);
        randomiseMatrix(matrix2, sizes[i]);
        start = clock();
        Matrix::consistentDotMultiplication(matrix1, matrix2, result, sizes[i]);
        end = clock();
        consistentDotResults.push_back(end - start);
        makeZeroMatrix(result, sizes[i]);
        start = clock();
        Matrix::parallelDotMultiplication(matrix1, matrix2, result, sizes[i], threadNum, 1);
        end = clock();
        parallelDotResults.push_back(end - start);
        for (int j = 0; j < 5; j++) {
            fout << blockSizes[j] << " ";
            randomiseMatrix(matrix1, sizes[i]);
            randomiseMatrix(matrix2, sizes[i]);
            start = clock();
            Matrix::consistentBlockMultiplication(matrix1, matrix2, result, sizes[i], blockSizes[j]);
            end = clock();
            fout << end - start << " ";
            makeZeroMatrix(result, sizes[i]);
            start = clock();
            Matrix::parallelBlockMultiplication(matrix1, matrix2, result, sizes[i], threadNum, blockSizes[j], 1);
            end = clock();
            fout << end - start << " ";
            makeZeroMatrix(result, sizes[i]);
            start = clock();
            Matrix::parallelBlockMultiplication(matrix1, matrix2, result, sizes[i], threadNum, blockSizes[j], 2);
            end = clock();
            fout << end - start << endl;
        }
    }
    fout.close();
}