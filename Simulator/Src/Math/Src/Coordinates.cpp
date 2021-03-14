#include <Coordinates.hpp>
#include <cmath>

Coordinates::Coordinates() : latitude(0), longitude(0){

}

Coordinates::Coordinates(const Coordinates::Latitude& latitude, const Coordinates::Longitude& longitude)
    : latitude(latitude), longitude(longitude){

}

std::tuple<unsigned int, unsigned int, float, bool> Coordinates::ddToDms(const double& dd) {
    const bool isPositive = dd >= 0.;
    const double absoluteValue = std::abs(dd);
    const unsigned int degrees = std::floor(absoluteValue);
    const double minutesInDouble = (absoluteValue - degrees) * 60.;
    const unsigned int minutes = std::floor(minutesInDouble);
    const float seconds = static_cast<float>(minutesInDouble - minutes) * 60.f;

    return {degrees, minutes, seconds, isPositive};
}

std::tuple<unsigned int, unsigned int, float, char> Coordinates::getHumanReadableLatitude() const {
    const auto [d, m, s, isPositive] = ddToDms(latitude);
    return {d, m, s, isPositive ? 'N' : 'S'};
}

std::tuple<unsigned int, unsigned int, float, char> Coordinates::getHumanReadableLongitude() const {
    const auto [d, m, s, isPositive] = ddToDms(longitude);
    return {d, m, s, isPositive ? 'E' : 'W'};
}

double Coordinates::distanceBetween(const Coordinates &first, const Coordinates &second) {
    // Calculations are done using Haversine formula
    static constexpr auto d2r = [](double deg) -> double{
        return deg * M_PI / 180.;
    };

    const double deltaLatitude = second.latitude - first.latitude;
    const double deltaLongitude = second.longitude - first.longitude;

    const double a = std::pow(std::sin(d2r(deltaLatitude / 2.)), 2) +
            std::cos(d2r(first.latitude)) * std::cos(d2r(second.latitude)) * std::pow(std::sin(d2r(deltaLongitude / 2.)), 2);

    const double c = 2. * std::atan2(std::sqrt(a), std::sqrt(1. - a));
    const double d = earthRadius * c;

    return d;
}

double Coordinates::initialBearing(const Coordinates &destination) const {
    static constexpr auto d2r = [](double deg) -> double{
        return deg * M_PI / 180.;
    };

    const double deltaLongitude = destination.longitude - longitude;
    const double y = std::sin(d2r(deltaLongitude)) * std::cos(d2r(destination.latitude));
    const double x = std::cos(d2r(latitude)) * std::sin(d2r(destination.latitude)) -
            std::sin(d2r(latitude)) * std::cos(d2r(destination.latitude)) * std::cos(d2r(deltaLongitude));
    const double angleInDegrees = std::atan2(y, x) * 180. / M_PI;

    return std::fmod(angleInDegrees + 360., 360.);
}
