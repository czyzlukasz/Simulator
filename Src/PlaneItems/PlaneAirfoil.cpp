#include <PlaneItems/PlaneAirfoil.hpp>
#include <PlaneStatus.hpp>
#include <map>
#include <cmath>

PlaneAirfoil::PlaneAirfoil(const Vector3d &distanceFromCenterOfMass,
                           const Vector3d &momentOfInertia,
                           double mass,
                           double area,
                           const Quaterniond &airfoilDirection)
    : PlaneItem(distanceFromCenterOfMass, momentOfInertia, mass),
      area(area),
      airfoilDirection(airfoilDirection){

}

std::string PlaneAirfoil::debugPrint() const {
    return std::string();
}

Vector3d PlaneAirfoil::calculateResultingForce(const PlaneStatus &planeStatus) const {
    static constexpr auto directionVectorToEuler = [](const Vector3d& directionVector) -> std::optional<Vector3d>{
        if(const auto normalized = directionVector.normalized()){
            const Vector3d vec = Vector3d(normalized.value());
            const double yaw = std::atan2( vec.y(), vec.x()) * 180. / M_PI;
            const double pitch = std::asin(-vec.z()) * 180. / M_PI;

            return Vector3d(0, std::fmod(pitch + 360., 360.), std::fmod(yaw + 360., 360.));
        }
        return std::nullopt;
    };

    const double weight = getMass() * 9.81;
    Vector3d result = Vector3d(0, 0, weight);

    if(const auto planeDirectionInEulerAngles = directionVectorToEuler(planeStatus.speed)){
        const Quaterniond directionRotation(Vector3d(0, -planeDirectionInEulerAngles->y(), -planeDirectionInEulerAngles->z()));
        const Quaterniond airfoilRotationRelativeToVelocity = directionRotation * planeStatus.rotation * airfoilDirection;

        const Vector3d eulerAngle = airfoilRotationRelativeToVelocity.toEulerAngles();
        const double speed = planeStatus.speed.length()
                * std::abs(std::cos(eulerAngle.z() * M_PI / 180.));
        const double aoa = eulerAngle.y();
        const double liftCoefficient = calculateLiftCoefficient(aoa);
        const double dragCoefficient = calculateDragCoefficient(aoa);

        const double liftForce = liftCoefficient * speed * speed * airDensity * area * 0.5;
        const double dragForce = dragCoefficient * speed * speed * airDensity * area * 0.5;

        const Vector3d combinedForces = Vector3d(-dragForce, 0, -liftForce).rotatedByQuaternion(planeStatus.rotation * airfoilDirection);
        result = result + combinedForces;
    }

    return result;
}

double PlaneAirfoil::calculateLiftCoefficient(double aoa) {
    static const std::map<int, double> lut = {
            {-20, -1.65},
            {-15, -1.5},
            {-10, -0.95},
            {-5, -0.4},
            {0, 0.2},
            {5, 0.75},
            {10, 1.3},
            {15, 1.7},
            {20, 1.8},
            {25, 1.35}
    };
    constexpr int step = 5;
    const int roundedDown = static_cast<int>(std::floor(aoa));
    // Round to lower multiple of step
    const int lowerBound = roundedDown >= 0 ? (roundedDown / step) * step : -((-roundedDown / step) * step);
    const int upperBound = lowerBound + step;

    if(const auto lowerIt = lut.find(lowerBound); lowerIt != lut.end()) {
        if(const auto upperIt = lut.find(upperBound); upperIt != lut.end()) {
            const double lowerValue = lowerIt->second;
            const double upperValue = upperIt->second;

            // Use linear interpolation
            const double result = (lowerValue * (upperBound - aoa) + upperValue * (aoa - lowerBound)) / (upperBound - lowerBound);

            return result;
        }
    }

    return 0.;
}

double PlaneAirfoil::calculateDragCoefficient(double aoa) {
    // TODO: copypaste, will be fixed with proper LUT passed by user
    static const std::map<int, double> lut = {
            {-20, 0.04},
            {-15, 0.016},
            {-10, 0.01},
            {-5, 0.006},
            {0, 0.004},
            {5, 0.006},
            {10, 0.01},
            {15, 0.016},
            {20, 0.04},
            {25, 0.2},
    };
    constexpr int step = 5;
    const int roundedDown = static_cast<int>(std::floor(aoa));
    // Round to lower multiple of step
    const int lowerBound = roundedDown >= 0 ? (roundedDown / step) * step : -((-roundedDown / step) * step);
    const int upperBound = lowerBound + step;

    if(const auto lowerIt = lut.find(lowerBound); lowerIt != lut.end()) {
        if(const auto upperIt = lut.find(upperBound); upperIt != lut.end()) {
            const double lowerValue = lowerIt->second;
            const double upperValue = upperIt->second;

            // Use linear interpolation
            const double result = (lowerValue * (upperBound - aoa) + upperValue * (aoa - lowerBound)) / (upperBound - lowerBound);

            return result;
        }
    }

    return 0.2;
}
