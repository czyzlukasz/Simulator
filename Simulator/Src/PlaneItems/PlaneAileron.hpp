#ifndef PLANEAILERON_HPP
#define PLANEAILERON_HPP

#include <PlaneItems/PlaneAirfoil.hpp>


struct PlaneAileron : public PlaneAirfoil {
    PlaneAileron(const Vector3d& distanceFromCenterOfMass,
                 const Vector3d& momentOfInertia,
                 double mass,
                 double area,
                 const Quaterniond& airfoilDirection,
                 const std::string& angleParameterName);

private:
    const std::string angleParameterName;
};


#endif //SIMULATOR_PLANEAILERON_HPP
