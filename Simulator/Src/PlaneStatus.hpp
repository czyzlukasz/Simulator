#ifndef PLANESTATUS_HPP
#define PLANESTATUS_HPP

#include <Configuration.hpp>
#include <variant>
#include <map>
#include <cstdint>
#include <string>

struct PlaneStatus {
    PlaneStatus();
    // Position will be later converted to Geographic coordinate system
    Vector3d position;
    Vector3d speed;
    Quaterniond rotation;

    std::map<std::string, std::variant<float, uint32_t>> parameters;
};


#endif //PLANESTATUS_HPP
