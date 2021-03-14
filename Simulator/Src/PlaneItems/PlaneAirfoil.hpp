#ifndef PLANEAIRFOIL_HPP
#define PLANEAIRFOIL_HPP

#include <PlaneItem.hpp>


struct PlaneAirfoil : public PlaneItem{
    PlaneAirfoil(const Vector3d &distanceFromCenterOfMass,
                 const Vector3d &momentOfInertia,
                 double mass,
                 double area,
                 const Quaterniond& airfoilDirection);

    virtual std::string debugPrint() const override;
    virtual Vector3d calculateResultingForce(const PlaneStatus& planeStatus) const override;

    // TODO: Allow user to specify LUT for Lift Coefficient of an airfoil
    static double calculateLiftCoefficient(double aoa);
    static double calculateDragCoefficient(double aoa);

protected:
    const double area;
    mutable Quaterniond airfoilDirection;
    static constexpr double airDensity = 1.225;
};


#endif //PLANEAIRFOIL_HPP
