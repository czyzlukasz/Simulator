#ifndef MATH3DCPP_QUATERNION_HPP
#define MATH3DCPP_QUATERNION_HPP


template<typename TYPE>
struct Vector3;
template<unsigned int DIM, typename TYPE>
struct Matrix;

/**
 * @brief Quaternion implementation
 * @tparam TYPE Underlying type that is used to store data and perform calculation. Only float and double are supported.
 */
template<typename TYPE>
struct Quaternion {
    Quaternion() = default;
    /**
     * @brief Constructor that converts Euler angles (Roll, Pitch, Yaw) to a quaternion
     * @param eulerAngles Vector containing RPY angles in degrees
     */
    Quaternion(const Vector3<TYPE>& eulerAngles);
    /**
     * @brief Constructor for 'raw' quaternion
     * @param w W
     * @param x X
     * @param y Y
     * @param z Z
     */
    Quaternion(TYPE w, TYPE x, TYPE y, TYPE z);

    /**
     * @brief Convert quaternion to Euler representation
     * @return Vector containing RPY angles in degrees
     * @see Quaternion::Quaternion(const Vector3<TYPE>& eulerAngles)
     */
    Vector3<TYPE> toEulerAngles() const;
    /**
     * @brief Calculate length (norm) of a quaternion
     * @return Scalar value representing norm of a quaternion
     */
    TYPE length() const;
    /**
     * @brief Calculate unit quaternion
     * @return Quaternion that has norm equal to 1
     */
    Quaternion<TYPE> normalized() const;
    /**
     * @brief Calculate q^-1
     * @return Reciprocal of current quaternion
     */
    Quaternion<TYPE> reciprocated() const;
    /**
     * @brief Calculate rotation matrix
     * @return 3x3 matrix that represents rotation in 3D space based on current quaternion
     * @see Matrix
     */
    Matrix<3, TYPE> toRotationMatrix() const;

    /**
     * @brief Multiplication of two quaternions
     * @param other Quaternion that is a multiplier
     * @return Quaternion that is a result of multiplication
     */
    Quaternion<TYPE> operator*(const Quaternion<TYPE>& other) const;

    TYPE w;
    TYPE x;
    TYPE y;
    TYPE z;
};


#endif //MATH3DCPP_QUATERNION_HPP
