#include <RigidBody.hpp>

template struct IterationData<float>;
template struct IterationData<double>;
template struct RigidBody<float>;
template struct RigidBody<double>;


template<typename TYPE>
void IterationData<TYPE>::setIterationLength(TYPE duration) {
    tickDuration = duration;
}

template<typename TYPE>
void IterationData<TYPE>::addActingForce(const Vector3<TYPE>& localForce, const Vector3<TYPE>& distanceFromCenterOfMass) {
    // TODO: Add +=, -=, /= and *= to VectorImpl
    force = force + localForce;
    torque = torque + Vector3<TYPE>::cross(distanceFromCenterOfMass, localForce);
}

template<typename TYPE>
bool RigidBody<TYPE>::iterate(const IterationData<TYPE>& iterationData) {
    const TYPE& deltaT = iterationData.tickDuration;
    if(deltaT <= 0 || mass <= 0 || momentOfInertia.x() <= 0 || momentOfInertia.y() <= 0 || momentOfInertia.z() <= 0){
        return false;
    }

    // Translation
    const Vector3<TYPE> acceleration = iterationData.force / mass;
    const Vector3<TYPE> deltaV = acceleration * deltaT;

    velocity = velocity + deltaV;
    position = position + velocity * deltaT;

    // Rotation
    const Vector3<TYPE> angularAcceleration = iterationData.torque / momentOfInertia;
    const Vector3<TYPE> deltaOmega = angularAcceleration * deltaT;

    angularVelocity = angularVelocity + deltaOmega;
    // Combine two rotations
    rotation = Quaternion<TYPE>(angularVelocity * deltaT) * rotation;

    return true;
}
