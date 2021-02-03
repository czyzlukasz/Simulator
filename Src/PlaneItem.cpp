#include <PlaneItem.hpp>

PlaneItem::PlaneItem(const Vector3d &distanceFromCenterOfMass, const Vector3d &momentOfInertia, double mass)
        : distanceFromCenterOfMass(distanceFromCenterOfMass), momentOfInertia(momentOfInertia), mass(mass){

}

const Vector3d& PlaneItem::getDostanceFromCenterOfMass() const {
    return distanceFromCenterOfMass;
}

const Vector3d& PlaneItem::getMomentOfInertia() const {
    return momentOfInertia;
}

double PlaneItem::getMass() const {
    return mass;
}
