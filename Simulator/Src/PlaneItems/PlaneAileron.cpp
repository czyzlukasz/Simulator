#include <PlaneItems/PlaneAileron.hpp>
#include <Math/Src/Configuration.hpp>

PlaneAileron::PlaneAileron(const Vector3d& distanceFromCenterOfMass,
                           const Vector3d& momentOfInertia,
                           double mass,
                           double area,
                           const Quaterniond& airfoilDirection,
                           const std::string& angleParameterName)
    : PlaneAirfoil(distanceFromCenterOfMass, momentOfInertia, mass, area, airfoilDirection),
      angleParameterName(angleParameterName){

}
