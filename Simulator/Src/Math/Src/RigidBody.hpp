#ifndef MATH3DCPP_RIGIDBODY_HPP
#define MATH3DCPP_RIGIDBODY_HPP

#include <Vector.hpp>
#include <Quaternion.hpp>


/**
 *
 * @tparam TYPE Underlying type that is used to store data and perform calculation. Only float and double are supported.
 */
template <typename TYPE>
struct IterationData{
    IterationData() = default;
    /**
     * @brief Set length of tick that forces set by addActingForce are being applied
     * @param duration Duration of tick in seconds
     */
    void setIterationLength(TYPE duration);

    /**
     * @brief Add force acting on rigid body that acts in current tick
     * @param localForce Vector of force. Length of vector indicates force amplitude in Newtons
     * @param distanceFromCenterOfMass Vector specifying point of rigid body that force is being applied on
     */
    void addActingForce(const Vector3<TYPE>& localForce, const Vector3<TYPE>& distanceFromCenterOfMass);

    TYPE tickDuration;
    Vector3<TYPE> torque;
    Vector3<TYPE> force;
};


template <typename TYPE>
struct RigidBody {
    /**
     * @brief Default constructor setting initial conditions to zero
     */
    RigidBody() = default;

    /**
     * @brief Perform iteration based on data passed in IterationData
     * @param iterationData Aggregated data
     * @return True if iteration is successful
     */
    [[nodiscard]] bool iterate(const IterationData<TYPE>& iterationData);

    /**
     * @brief Mass of the body in kilograms
     */
    TYPE mass;

    /**
     * @brief Position of the body in meters relative to origin
     */
    Vector3<TYPE> position;

    /**
     * @brief Velocity in m/s of the center of rigid body
     */
    Vector3<TYPE> velocity;

    /**
     * @brief Moment of inertia of the body in kg * m * m
     */
    Vector3<TYPE> momentOfInertia;

    /**
     * @brief Rotation of the body relative to space in degrees
     */
    Quaternion<TYPE> rotation;

    /**
     * @brief Angular velocity in deg/s around the center of rigid body
     */
    Vector3<TYPE> angularVelocity;
};

#endif //MATH3DCPP_RIGIDBODY_HPP
