#ifndef MATH3DCPP_VECTORIMPL_HPP
#define MATH3DCPP_VECTORIMPL_HPP

#include <optional>
#include <initializer_list>
#include <array>


template<typename TYPE>
struct Quaternion;

/**
 * @brief Implementation of Vectors
 * @tparam DIM Length of a vector
 * @tparam TYPE Underlying type that is used to store data and perform calculation. Only float and double are supported.
 */
template<unsigned int DIM, typename TYPE>
struct VectorImpl {
    /**
     * @brief Default constructor that creates null-vector
     */
    VectorImpl();

    /**
     * @brief Constructor that initializes vector's members
     * @tparam T Type of elements passed as arguments
     * @param initialValues Values of each vector's member starting from a first element
     */
    template<typename... T>
    VectorImpl(T... initialValues) : values{initialValues...}{};

    /**
     * @brief Copy constructor
     * @param other constructor to be copied
     */
    VectorImpl(const VectorImpl<DIM, TYPE>& other) = default;

    /**
     * @brief Calculate length of a vector
     * @return Length of a vector
     */
    TYPE length() const;
    /**
     * @brief Calculate normalized vector based on current vector
     * @return Vector of length equal to 1 or std::nullopt if length of current vector is equal to 0
     */
    std::optional<VectorImpl<DIM, TYPE>> normalized() const;
    /**
     * @brief Rotate vector by a quaternion
     * @param quaternion Quaternion used to rotate current vector
     * @return New vector that is rotated by quaternion
     * @see Quaternion
     */
    VectorImpl<DIM, TYPE> rotatedByQuaternion(const Quaternion<TYPE>& quaternion) const;

    /**
     * @brief Vector operators
     * @return Calculated vector
     * @{
     */
    VectorImpl<DIM, TYPE> operator/(TYPE other) const;
    VectorImpl<DIM, TYPE> operator/(const VectorImpl<DIM, TYPE>& other) const;
    VectorImpl<DIM, TYPE> operator*(TYPE other) const;
    VectorImpl<DIM, TYPE> operator*(const VectorImpl<DIM, TYPE>& other) const;
    VectorImpl<DIM, TYPE> operator+(const VectorImpl<DIM, TYPE>& other) const;
    VectorImpl<DIM, TYPE> operator-(const VectorImpl<DIM, TYPE>& other) const;
    VectorImpl<DIM, TYPE> operator-() const;
    /** @} */

    /**
     * @brief Comparison operator
     * @param other Vector to be compared to
     * @return True if vectors are identical
     */
    bool operator == (const VectorImpl<DIM, TYPE>& other) const;

    std::array<TYPE, DIM> values;
};


#endif //MATH3DCPP_VECTORIMPL_HPP
