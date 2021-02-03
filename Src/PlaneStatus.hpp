#ifndef PLANESTATUS_HPP
#define PLANESTATUS_HPP

#include <Configuration.hpp>


struct PlaneStatus {
    PlaneStatus();
    // Position will be later converted to Geographic coordinate system
    Vector3d position;
    Vector3d speed;
    Quaterniond rotation;
};


#endif //PLANESTATUS_HPP
