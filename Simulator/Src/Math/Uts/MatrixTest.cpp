#include <gtest/gtest.h>
#include <Matrix.hpp>

using Matrix3d = Matrix<3, double>;

TEST(MatrixTest, NonZeroDeterminant){
    const Matrix3d matrix({
        {-1, 2, 1},
        {3, -1, 2},
        {1, -2, 3}
    });

    EXPECT_DOUBLE_EQ(matrix.determinant(), -20.);
}

TEST(MatrixTest, ZeroDeterminant){
    const Matrix3d matrix({
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 6}
    });

    EXPECT_DOUBLE_EQ(matrix.determinant(), 0.);
}

TEST(MatrixTest, MultiplyByMatrix){
    const Matrix3d matrix1({
        {5, 6, 1},
        {8, 7, 9},
        {1, 5, 2}
    });
    const Matrix3d matrix2({
       {4, 6, 7},
       {2, 5, 1},
       {0, 3, 9}
    });
    const Matrix3d expectedResult({
       {32, 63, 50},
       {46, 110, 144},
       {14, 37, 30}
    });

    const Matrix3d result = matrix1 * matrix2;
    EXPECT_EQ(result, expectedResult);
}

TEST(MatrixTest, AddTwoMatrices){
    const Matrix3d matrix1({
       {5, 6, 1},
       {8, 7, 9},
       {1, 5, 2}
    });
    const Matrix3d matrix2({
       {4, 6, 7},
       {2, 5, 1},
       {0, 3, 9}
    });
    const Matrix3d expectedResult({
      {9, 12, 8},
      {10, 12, 10},
      {1, 8, 11}
    });

    const Matrix3d result = matrix1 + matrix2;
    EXPECT_EQ(result, expectedResult);
}

TEST(MatrixTest, SubtractTwoMatrices){
    const Matrix3d matrix1({
       {5, 6, 1},
       {8, 7, 9},
       {1, 5, 2}
    });
    const Matrix3d matrix2({
       {4, 6, 7},
       {2, 5, 1},
       {0, 3, 9}
    });
    const Matrix3d expectedResult({
      {1, 0, -6},
      {6, 2, 8},
      {1, 2, -7}
    });

    const Matrix3d result = matrix1 - matrix2;
    EXPECT_EQ(result, expectedResult);
}

TEST(MatrixTest, MultiplyByScalar){
    const Matrix3d matrix({
      {1, 0, -6},
      {6, 2, 8},
      {1, 2, -7}
    });
    const Matrix3d expectedResult({
      {0.75, 0, -4.5},
      {4.5, 1.5, 6},
      {0.75, 1.5, -5.25}
    });

    const Matrix3d result = matrix * 0.75;
    EXPECT_EQ(result, expectedResult);
}

TEST(MatrixTest, CheckIfEqual){
    const Matrix3d matrix1({
        {1, 0, -6},
        {6, 2, 8},
        {1, 2, -7}
    });
    const Matrix3d matrix2({
      {0.75, 0, -4.5},
      {4.5, 1.5, 6},
      {0.75, 1.5, -5.25}
    });

    EXPECT_NE(matrix1, matrix2);
}
