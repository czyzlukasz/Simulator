#ifndef PLANEITEMMOCK_HPP
#define PLANEITEMMOCK_HPP

#include <gmock/gmock.h>

struct PlaneItemMock : public PlaneItem{
    PlaneItemMock(const Vector3d &distanceFromCenterOfMass, const Vector3d &momentOfInertia, double mass)
        : PlaneItem(distanceFromCenterOfMass, momentOfInertia, mass){}

    MOCK_CONST_METHOD0(debugPrint, std::string());
    MOCK_CONST_METHOD1(calculateResultingForce, Vector3d(const PlaneStatus& planeStatus));
};
#endif //PLANEITEMMOCK_HPP
