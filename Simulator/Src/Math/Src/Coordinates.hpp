#ifndef MATH3DCPP_COORDINATES_HPP
#define MATH3DCPP_COORDINATES_HPP


#include <tuple>


/**
 * @brief Utility for calculating position and orientation in Geographic Coordinates System
 */
struct Coordinates {

    /**
     * @brief North-South position
     */
    struct Latitude{
        /**
         * @param value Position in degrees. Accepted value ranges from -90 to 90
         */
        constexpr explicit Latitude(double value) : value(value){}
        constexpr operator double () const{
            return value;
        }

        double value;
    };

    /**
     * @brief East-West position
     */
    struct Longitude{
        /**
         * @param value Position in degrees. Accepted value ranges from -180 to 180
         */
        constexpr explicit Longitude(double value) : value(value){}
        constexpr operator double () const{
            return value;
        }
        double value;
    };

    /**
     * @brief Default constructor that sets coordinates to 0N 0E
     */
    Coordinates();

    /**
     * @brief Standard constructor used to set latitude and longitude
     * @param latitude Latitude must be explicitly passed by Latitude struct
     * @param longitude Longitude must be explicitly passed by Longitude struct
     * @see Latitude
     * @see Longitude
     */
    Coordinates(const Latitude& latitude, const Longitude& longitude);

private:
    static std::tuple<unsigned int, unsigned int, float, bool> ddToDms(const double& dd);

public:
    /**
     * @brief Convert Latitude in DD to DMS format
     * This function converts decimal representation (-12.345) into Degrees-Minutes-Seconds (12° 20' 42" S/W).
     * Note that returned degrees are always non-negative and direction is noted by direction character (N, E, S or W).
     * @return Tuple in format [Degrees, Minutes, Seconds, Direction Character]
     * @{
     */
    std::tuple<unsigned int, unsigned int, float, char> getHumanReadableLatitude() const;
    std::tuple<unsigned int, unsigned int, float, char> getHumanReadableLongitude() const;
    /** @} */

    /**
     * @brief Calculate distance between two points on Earth
     * Note that distance is calculated as shortest path along Earth's surface
     * @param first First point on Earth
     * @param second Second point on Earth
     * @return Distance between two points in meters
     */
    static double distanceBetween(const Coordinates& first, const Coordinates& second);

    /**
     * @brief Calculate bearing (forward azimuth) from current coordinates to a destination
     * @param Destination Point on Earth's surface that initial bearing will aim towards
     * @return Bearing in degrees
     */
    double initialBearing(const Coordinates& destination) const;

    Latitude latitude;
    Longitude longitude;

private:
    static constexpr double earthRadius = 6.371e6;
};

/**
 * @brief User defined literals for verbose creation of coordinates
 * For example 12.3_S equals to Coordinates::Latitude(-12.3)
 * @param Position in degrees
 * @return Latitude or Longitude with proper value already set
 * @{
 */
constexpr Coordinates::Latitude operator "" _N (long double val){
    return Coordinates::Latitude(static_cast<double>(val));
}

constexpr Coordinates::Latitude operator "" _S (long double val){
    return Coordinates::Latitude(static_cast<double>(-val));
}

constexpr Coordinates::Longitude operator "" _E (long double val){
    return Coordinates::Longitude(static_cast<double>(val));
}

constexpr Coordinates::Longitude operator "" _W (long double val){
    return Coordinates::Longitude(static_cast<double>(-val));
}
/** @} */
#endif //MATH3DCPP_COORDINATES_HPP
