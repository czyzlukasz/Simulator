#ifndef MATH3DCPP_MATRIX_HPP
#define MATH3DCPP_MATRIX_HPP

#include <array>


/**
 * @brief Implementation of square matrices (n x n)
 * @tparam DIM Dimension of square matrix
 * @tparam TYPE Underlying type that is used to store data and perform calculation. Only float and double are supported.
 */
template<unsigned int DIM, typename TYPE>
struct Matrix {
    /**
     * @brief Underlying container used for storing martix's data
     */
    using ValueType = std::array<std::array<TYPE, DIM>, DIM>;

    /**
     * @brief Default constructor that initializes all values to 0
     */
    Matrix();
    /**
     * @brief Constructor that initializes entire matrix
     * Values are passed using square brackets method:\n
     * { {a11, a12, ..., a1n},\n
     *   {a21, a22, ..., a2n},\n
     *   ...\n
     *   {an1, an2, ..., ann} }\n
     * @param value Initializer list of initialier lists that contain all values
     */
    Matrix(std::initializer_list<std::initializer_list<TYPE>>&& value);

    /**
     * @brief Calculate determinant (DET) of matrix
     * @warning For now determinant can be calculated only for 3x3 matrices
     * @return Scalar value that is determinant of matrix
     */
    TYPE determinant() const;

    /**
     * @brief Matrix operator resulting in new matrix
     * @return Calculated matrix
     * @{
     */
    Matrix<DIM, TYPE> operator*(const Matrix<DIM, TYPE>& other) const;
    /**
     * @brief Scalar multiplication of every member of matrix
     * @param other Value used in multiplication
     * @return Calculated matrix
     */
    Matrix<DIM, TYPE> operator*(TYPE other) const;
    Matrix<DIM, TYPE> operator+(const Matrix<DIM, TYPE>& other) const;
    Matrix<DIM, TYPE> operator-(const Matrix<DIM, TYPE>& other) const;
    /** @} */

    /**
     * @brief Comparison operator for two matrices
     * Note that this operator allows for small absolute difference (1e-6) between matrices' members
     * @param other Matrix to be compared to
     * @return True if matrices are identical or very similar
     */
    bool operator==(const Matrix<DIM, TYPE>& other) const;
    bool operator!=(const Matrix<DIM, TYPE>& other) const;

    /**
     * @brief Container for matrix's elements
     * Individual element can be accessed by values[row][column]
     */
    ValueType values;
};


#endif //MATH3DCPP_MATRIX_HPP
