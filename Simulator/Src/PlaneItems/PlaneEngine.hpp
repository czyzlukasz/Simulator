#ifndef PLANEENGINE_HPP
#define PLANEENGINE_HPP

#include <PlaneItem.hpp>


struct PlaneEngine : public PlaneItem{
    PlaneEngine(const Vector3d &distanceFromCenterOfMass,
                const Vector3d &momentOfInertia,
                double mass,
                const Quaterniond& engineDirection,
                double maxThrust,
                const std::string& thrustParameterName);
    virtual std::string debugPrint() const override;
    virtual Vector3d calculateResultingForce(const PlaneStatus& planeStatus) const override;

private:
    const Quaterniond engineDirection;
    const Vector3d directionOfForce;
    double maxThrust;
    const std::string thrustParameterName;
};


#endif //PLANEENGINE_HPP
