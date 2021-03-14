#include <VectorImpl.hpp>
#include <cmath>
#include <numeric>
#include <Vector.hpp>
#include <Quaternion.hpp>

template struct VectorImpl<3, double>;
template struct VectorImpl<3, float>;
template struct VectorImpl<4, double>;
template struct VectorImpl<4, float>;

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE>::VectorImpl() : values(){

}

template<unsigned int DIM, typename TYPE>
TYPE VectorImpl<DIM, TYPE>::length() const {
    const auto sum = std::accumulate(values.cbegin(), values.cend(), 0., [](const TYPE sum, const TYPE value){
        return sum + value * value;});
    return std::sqrt(sum);
}

template<unsigned int DIM, typename TYPE>
std::optional<VectorImpl<DIM, TYPE>> VectorImpl<DIM, TYPE>::normalized() const {
    if(const TYPE det = length()){
        return *this / det;
    }
    return std::nullopt;
}

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE> VectorImpl<DIM, TYPE>::rotatedByQuaternion(const Quaternion<TYPE>& quaternion) const {
    const Quaternion<TYPE> quaternionReciprocated = quaternion.reciprocated();
    const Quaternion<TYPE> result = quaternion * Quaternion<TYPE>(0, values[0], values[1], values[2]) * quaternionReciprocated;
    // TODO: Find a way to avoid usage when DIM != 3
    return VectorImpl<DIM, TYPE>(result.x, result.y, result.z);
}

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE> VectorImpl<DIM, TYPE>::operator/(TYPE other) const {
    VectorImpl<DIM, TYPE> result;
    for(size_t idx = 0; idx < DIM; ++idx){
        result.values[idx] = values[idx] / other;
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE> VectorImpl<DIM, TYPE>::operator/(const VectorImpl<DIM, TYPE> &other) const {
    VectorImpl<DIM, TYPE> result;
    for(size_t idx = 0; idx < DIM; ++idx){
        result.values[idx] = values[idx] / other.values[idx];
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE> VectorImpl<DIM, TYPE>::operator*(TYPE other) const {
    VectorImpl<DIM, TYPE> result;
    for(size_t idx = 0; idx < DIM; ++idx){
        result.values[idx] = values[idx] * other;
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE> VectorImpl<DIM, TYPE>::operator*(const VectorImpl<DIM, TYPE> &other) const {
    VectorImpl<DIM, TYPE> result;
    for(size_t idx = 0; idx < DIM; ++idx){
        result.values[idx] = values[idx] * other.values[idx];
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE> VectorImpl<DIM, TYPE>::operator+(const VectorImpl<DIM, TYPE>& other) const{
    VectorImpl<DIM, TYPE> result;
    for(size_t idx = 0; idx < DIM; ++idx){
        result.values[idx] = values[idx] + other.values[idx];
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE> VectorImpl<DIM, TYPE>::operator-(const VectorImpl<DIM, TYPE>& other) const{
    VectorImpl<DIM, TYPE> result;
    for(size_t idx = 0; idx < DIM; ++idx){
        result.values[idx] = values[idx] - other.values[idx];
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
VectorImpl<DIM, TYPE> VectorImpl<DIM, TYPE>::operator-() const {
    VectorImpl<DIM, TYPE> result;
    for(size_t idx = 0; idx < DIM; ++idx){
        result.values[idx] = -values[idx];
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
bool VectorImpl<DIM, TYPE>::operator==(const VectorImpl<DIM, TYPE>& other) const {
    return values == other.values;
}
