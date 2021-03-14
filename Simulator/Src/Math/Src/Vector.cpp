#include <Vector.hpp>

template struct Vector3<double>;
template struct Vector3<float>;
template struct Vector4<double>;
template struct Vector4<float>;

template<typename TYPE>
Vector3<TYPE>::Vector3() : VectorImpl<3, TYPE>(){

}

template<typename TYPE>
Vector3<TYPE>::Vector3(TYPE x, TYPE y, TYPE z) : VectorImpl<3, TYPE>({x, y, z}){

}

template<typename TYPE>
Vector3<TYPE>::Vector3(const VectorImpl<3, TYPE>& vector) : VectorImpl<3, TYPE>(vector){

}

template<typename TYPE>
Vector3<TYPE> Vector3<TYPE>::cross(const Vector3<TYPE> &first, const Vector3<TYPE> &second) {
    return Vector3<TYPE>(
            first.y() * second.z() - first.z() * second.y(),
            first.z() * second.x() - first.x() * second.z(),
            first.x() * second.y() - first.y() * second.x());
}

template<typename TYPE>
TYPE& Vector3<TYPE>::x() {
    return this->values[0];
}

template<typename TYPE>
TYPE& Vector3<TYPE>::y() {
    return this->values[1];
}

template<typename TYPE>
TYPE& Vector3<TYPE>::z() {
    return this->values[2];
}

template<typename TYPE>
const TYPE& Vector3<TYPE>::x() const{
    return this->values[0];
}

template<typename TYPE>
const TYPE& Vector3<TYPE>::y() const{
    return this->values[1];
}

template<typename TYPE>
const TYPE& Vector3<TYPE>::z() const{
    return this->values[2];
}

template<typename TYPE>
Vector4<TYPE>::Vector4() : VectorImpl<4, TYPE>(){

}

template<typename TYPE>
Vector4<TYPE>::Vector4(TYPE a, TYPE b, TYPE c, TYPE d) : VectorImpl<4, TYPE>({a, b, c, d}){

}

template<typename TYPE>
Vector4<TYPE>::Vector4(const VectorImpl<4, TYPE>& vector) : VectorImpl<4, TYPE>(vector){

}

template<typename TYPE>
TYPE& Vector4<TYPE>::a() {
    return this->values[0];
}

template<typename TYPE>
TYPE& Vector4<TYPE>::b() {
    return this->values[1];
}

template<typename TYPE>
TYPE& Vector4<TYPE>::c() {
    return this->values[2];
}

template<typename TYPE>
TYPE& Vector4<TYPE>::d() {
    return this->values[3];
}

template<typename TYPE>
const TYPE& Vector4<TYPE>::a() const{
    return this->values[0];
}

template<typename TYPE>
const TYPE& Vector4<TYPE>::b() const{
    return this->values[1];
}

template<typename TYPE>
const TYPE& Vector4<TYPE>::c() const{
    return this->values[2];
}
template<typename TYPE>
const TYPE& Vector4<TYPE>::d() const{
    return this->values[3];
}
