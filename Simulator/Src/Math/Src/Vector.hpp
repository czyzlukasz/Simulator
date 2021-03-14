#ifndef MATH3DCPP_VECTOR_HPP
#define MATH3DCPP_VECTOR_HPP

#include <VectorImpl.hpp>


/**
 * @brief Implementation of 3D Vector
 * @tparam TYPE Underlying type that is used to store data and perform calculation. Only float and double are supported.
 */
template<typename TYPE>
struct Vector3 : VectorImpl<3, TYPE>{
    /**
     * @brief Default constructor for null-vector
     */
    Vector3();
    /**
     * @brief Constructor for setting all members
     * @param x X
     * @param y Y
     * @param z Z
     */
    Vector3(TYPE x, TYPE y, TYPE z);
    /**
     * @brief Copy constructor
     * @param vector Vector to be copied
     */
    Vector3(const VectorImpl<3, TYPE>& vector);

    /**
     * @brief Cross product of two vectors
     * @param first
     * @param second
     * @return Vector that is a result of calculating first x second
     */
    static Vector3<TYPE> cross(const Vector3<TYPE>& first, const Vector3<TYPE>& second);

    /**
     * Getters for each parameter
     * @return Reference to given member
     * @{
     */
    TYPE& x();
    TYPE& y();
    TYPE& z();

    const TYPE& x() const;
    const TYPE& y() const;
    const TYPE& z() const;
    /** @} */
};

/**
 * @brief Implementation of 4D Vector
 * @tparam TYPE Underlying type that is used to store data and perform calculation. Only float and double are supported.
 */
template<typename TYPE>
struct Vector4 : VectorImpl<4, TYPE>{
    /**
    * @brief Default constructor for null-vector
    */
    Vector4();
     /**
      * @brief Constructor for setting all members
      * @param a A
      * @param b B
      * @param c C
      * @param d D
      */
    Vector4(TYPE a, TYPE b, TYPE c, TYPE d);
    /**
     * @brief Copy constructor
     * @param vector Vector to be copied
     */
    Vector4(const VectorImpl<4, TYPE>& vector);

    /**
    * Getters for each parameter
    * @return Reference to given member
    * @{
    */
    TYPE& a();
    TYPE& b();
    TYPE& c();
    TYPE& d();

    const TYPE& a() const;
    const TYPE& b() const;
    const TYPE& c() const;
    const TYPE& d() const;
    /** @} */
};



#endif //MATH3DCPP_VECTOR_HPP
