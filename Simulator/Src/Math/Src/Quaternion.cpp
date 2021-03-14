#include <Quaternion.hpp>
#include <cmath>
#include <Vector.hpp>
#include <Matrix.hpp>

template struct Quaternion<double>;
template struct Quaternion<float>;


template<typename TYPE>
Quaternion<TYPE>::Quaternion(const Vector3<TYPE>& eulerAngles) {
    // Convert degrees to radians
    constexpr auto d2r = [](TYPE degrees) -> TYPE{
        return degrees / 180. * M_PI;
    };

    const TYPE cr = std::cos(d2r(eulerAngles.x()) / 2.);
    const TYPE sr = std::sin(d2r(eulerAngles.x()) / 2.);
    const TYPE cp = std::cos(d2r(eulerAngles.y()) / 2.);
    const TYPE sp = std::sin(d2r(eulerAngles.y()) / 2.);
    const TYPE cy = std::cos(d2r(eulerAngles.z()) / 2.);
    const TYPE sy = std::sin(d2r(eulerAngles.z()) / 2.);

    w = cr * cp * cy + sr * sp * sy;
    x = sr * cp * cy - cr * sp * sy;
    y = cr * sp * cy + sr * cp * sy;
    z = cr * cp * sy - sr * sp * cy;
}

template<typename TYPE>
Quaternion<TYPE>::Quaternion(TYPE w, TYPE x, TYPE y, TYPE z) : w(w), x(x), y(y), z(z){

}

template<typename TYPE>
Vector3<TYPE> Quaternion<TYPE>::toEulerAngles() const {
    Vector3<TYPE> result;
    result.x() = std::atan2(2. * (w * x + y * z), 1. - 2. * (x * x + y * y));
    result.y() = std::asin(2. * (w * y - z * x));
    result.z() = std::atan2(2. * (w * z + x * y), 1. - 2. * (y * y + z * z));
    // Convert radians to degrees
    constexpr auto r2d = [](TYPE degrees) -> TYPE{
        return degrees / M_PI * 180.;
    };
    result.x() = r2d(result.x());
    result.y() = r2d(result.y());
    result.z() = r2d(result.z());

    return result;
}

template<typename TYPE>
TYPE Quaternion<TYPE>::length() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

template<typename TYPE>
Quaternion<TYPE> Quaternion<TYPE>::normalized() const {
    const TYPE den = length();
    return Quaternion<TYPE>(w / den, x / den, y / den, z / den);
}

template<typename TYPE>
Quaternion<TYPE> Quaternion<TYPE>::reciprocated() const {
    const Quaternion<TYPE> conjugatedQuaternion(w, -x, -y, -z);
    const TYPE normSquared = std::pow(length(), 2);
    return Quaternion<TYPE> (conjugatedQuaternion.w / normSquared,
                             conjugatedQuaternion.x / normSquared,
                             conjugatedQuaternion.y / normSquared,
                             conjugatedQuaternion.z / normSquared);
}

template<typename TYPE>
Matrix<3, TYPE> Quaternion<TYPE>::toRotationMatrix() const {
    const Quaternion<TYPE> n = normalized();
    return Matrix<3, TYPE> {
        {1 - 2 * n.y * n.y - 2 * n.z * n.z, 2 * n.x * n.y - 2 * n.z * n.w, 2 * n.x * n.z + 2 * n.y * n.w},
        {2 * n.x * n.y + 2 * n.z * n.w, 1 - 2 * n.x * n.x - 2 * n.z * n.z, 2 * n.y * n.z - 2 * n.x * n.w},
        {2 * n.x * n.z - 2 * n.y * n.w, 2 * n.y * n.z + 2 * n.x * n.w, 1 - 2 * n.x * n.x - 2 * n.y * n.y}
    };
}

template<typename TYPE>
Quaternion<TYPE> Quaternion<TYPE>::operator*(const Quaternion<TYPE> &other) const {
    const TYPE newW = w * other.w - x * other.x - y * other.y - z * other.z;
    const TYPE newX = w * other.x + x * other.w + y * other.z - z * other.y;
    const TYPE newY = w * other.y - x * other.z + y * other.w + z * other.x;
    const TYPE newZ = w * other.z + x * other.y - y * other.x + z * other.w;

    return Quaternion<TYPE>(newW, newX, newY, newZ);
}
