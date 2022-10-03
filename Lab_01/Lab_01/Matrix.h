#pragma once
#include <omp.h>
class Matrix
{
public:
	static void parallelBlockMultiplication(int** matrix1, int** matrix2, int** result, int N, int threadNum, int blockSize, int loopNum);
	static void consistentBlockMultiplication(int** matrix1, int** matrix2, int** result, int N, int blockSize);
	static void parallelDotMultiplication(int** matrix1, int** matrix2, int** result, int N, int threadNum, int loopNum);
	static void consistentDotMultiplication(int** matrix1, int** matrix2, int** result, int N);
};

