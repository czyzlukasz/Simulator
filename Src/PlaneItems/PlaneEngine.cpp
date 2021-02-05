#include <PlaneItems/PlaneEngine.hpp>
#include <PlaneStatus.hpp>


PlaneEngine::PlaneEngine(const Vector3d &distanceFromCenterOfMass,
                         const Vector3d &momentOfInertia,
                         double mass,
                         const Quaterniond &engineDirection,
                         double maxThrust,
                         const std::string& thrustParameterName)
    : PlaneItem(distanceFromCenterOfMass, momentOfInertia, mass),
      engineDirection(engineDirection),
      maxThrust(maxThrust),
      directionOfForce(Vector3d(1., 0., 0.).rotatedByQuaternion(engineDirection)),
      thrustParameterName(thrustParameterName){

}

std::string PlaneEngine::debugPrint() const {
    std::string result = "Engine: direction: ";
    result += std::to_string(engineDirection.toEulerAngles().x()) + ", ";
    result += std::to_string(engineDirection.toEulerAngles().y()) + ", ";
    result += std::to_string(engineDirection.toEulerAngles().z()) + ", ";
    result += "max thrust: " + std::to_string(maxThrust);

    return result;
}

Vector3d PlaneEngine::calculateResultingForce(const PlaneStatus& planeStatus) const {
    const Vector3d relativeDirectionOfForce = directionOfForce.rotatedByQuaternion(planeStatus.rotation);

    Vector3d result(0, 0, 0);
    // Calculate thrust based on direction, max thrust and thrust from plane parameters
    if(const auto it = planeStatus.parameters.find(thrustParameterName); it != planeStatus.parameters.cend()){
        if(const auto* thrust = std::get_if<float>(&it->second)) {
            result = relativeDirectionOfForce * maxThrust * (*thrust);
        }
    }

    // Add weight
    result = result + Vector3d(0, 0, 9.81 * getMass());

    return result;
}
