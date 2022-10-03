#include "pch.h"

class MatrixTest : public ::testing::TestWithParam<int> {


protected:
	int N = 3;
	int** matrix1;
	int** matrix2;
	int** correctResult;
	int** actualResult;
	MatrixTest() {
		matrix1 = (int**)malloc(sizeof(int*) * N);
		matrix2 = (int**)malloc(sizeof(int*) * N);
		correctResult = (int**)malloc(sizeof(int*) * N);
		actualResult = (int**)malloc(sizeof(int*) * N);
		for (int i = 0; i < N; i++) {
			matrix1[i] = (int*)malloc(sizeof(int) * N);
			matrix2[i] = (int*)malloc(sizeof(int) * N);
			correctResult[i] = (int*)malloc(sizeof(int) * N);
			actualResult[i] = (int*)malloc(sizeof(int) * N);
		}
		// initialize matrix1
		matrix1[0][0] = 5;
		matrix1[0][1] = -4;
		matrix1[0][2] = 8;
		matrix1[1][0] = 2;
		matrix1[1][1] = 3;
		matrix1[1][2] = 4;
		matrix1[2][0] = 0;
		matrix1[2][1] = -3;
		matrix1[2][2] = -7;

		// initialize matrix2
		matrix2[0][0] = 6;
		matrix2[0][1] = -2;
		matrix2[0][2] = 7;
		matrix2[1][0] = 4;
		matrix2[1][1] = 7;
		matrix2[1][2] = -1;
		matrix2[2][0] = 0;
		matrix2[2][1] = 5;
		matrix2[2][2] = -2;

		//initialize result
		correctResult[0][0] = 14;
		correctResult[0][1] = 2;
		correctResult[0][2] = 23;
		correctResult[1][0] = 24;
		correctResult[1][1] = 37;
		correctResult[1][2] = 3;
		correctResult[2][0] = -12;
		correctResult[2][1] = -56;
		correctResult[2][2] = 17;
	}

	~MatrixTest() {
		
	}

	void SetUp() override {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				actualResult[i][j] = 0;
			}
		}
	}
};

TEST_F(MatrixTest, consistentDotMultiplication_shouldMultiplyAsExpected) {
	Matrix::consistentDotMultiplication(matrix1, matrix2, actualResult, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ASSERT_EQ(actualResult[i][j], correctResult[i][j]);
		}
	}
	
}

TEST_F(MatrixTest, parallelDotMultiplication_shouldMultiplyAsExpected) {
	Matrix::parallelDotMultiplication(matrix1, matrix2, actualResult, N, 2, 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ASSERT_EQ(actualResult[i][j], correctResult[i][j]);
		}
	}
}

TEST_F(MatrixTest, consistentBlockMultiplication_shouldMultiplyAsExpected) {
	Matrix::consistentBlockMultiplication(matrix1, matrix2, actualResult, N, 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ASSERT_EQ(actualResult[i][j], correctResult[i][j]);
		}
	}
}

TEST_F(MatrixTest, parallelBlockMultiplication_shouldMultiplyAsExpected) {
	Matrix::parallelBlockMultiplication(matrix1, matrix2, actualResult, N, 2, 1, 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ASSERT_EQ(actualResult[i][j], correctResult[i][j]);
		}
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}