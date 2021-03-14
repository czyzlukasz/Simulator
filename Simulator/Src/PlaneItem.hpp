#ifndef PLANEITEM_HPP
#define PLANEITEM_HPP

#include <Math/Src/Configuration.hpp>
#include <string>

struct PlaneStatus;

// Base item simulating every part of the plane
struct PlaneItem {
    explicit PlaneItem(const Vector3d &distanceFromCenterOfMass, const Vector3d &momentOfInertia, double mass);
    virtual ~PlaneItem() = default;
    const Vector3d& getDostanceFromCenterOfMass() const;
    const Vector3d& getMomentOfInertia() const;
    double getMass() const;

    virtual std::string debugPrint() const = 0;
    virtual Vector3d calculateResultingForce(const PlaneStatus& planeStatus) const = 0;
private:
    const Vector3d distanceFromCenterOfMass;
    const Vector3d momentOfInertia;
    const double mass;
};


#endif //PLANEITEM_HPP
