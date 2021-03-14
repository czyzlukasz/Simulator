#include <Matrix.hpp>

template struct Matrix<4, double>;
template struct Matrix<4, float>;
template struct Matrix<3, double>;
template struct Matrix<3, float>;

template<unsigned int DIM, typename TYPE>
Matrix<DIM, TYPE>::Matrix() : values(){

}

template<unsigned int DIM, typename TYPE>
Matrix<DIM, TYPE>::Matrix(std::initializer_list<std::initializer_list<TYPE>>&& value) {
    for(size_t x = 0; x < DIM; ++x){
        const auto& column = value.begin() + x;
        for(size_t y = 0; y < DIM; ++y) {
            values[y][x] = *(column->begin() + y);
        }
    }
}

template<unsigned int DIM, typename TYPE>
TYPE Matrix<DIM, TYPE>::determinant() const {
    //TODO: implement determinant() for 4x4 matrices
//    static_assert(DIM == 3, "For now, determinant can be calculated only for 3x3 matrices");
    return values[0][0] * values[1][1] * values[2][2] +
           values[0][1] * values[1][2] * values[2][0] +
           values[0][2] * values[1][0] * values[2][1] -

           values[0][0] * values[1][2] * values[2][1] -
           values[0][1] * values[1][0] * values[2][2] -
           values[0][2] * values[1][1] * values[2][0];
}

template<unsigned int DIM, typename TYPE>
Matrix<DIM, TYPE> Matrix<DIM, TYPE>::operator*(const Matrix<DIM, TYPE>& other) const {
    Matrix<DIM, TYPE> result;
    for(size_t x = 0; x < DIM; ++x){
        for(size_t y = 0; y < DIM; ++y) {
            for(size_t idx = 0; idx < DIM; ++idx) {
                result.values[y][x] += values[idx][x] * other.values[y][idx];
            }
        }
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
Matrix<DIM, TYPE> Matrix<DIM, TYPE>::operator*(TYPE other) const {
    Matrix<DIM, TYPE> result;
    for(size_t x = 0; x < DIM; ++x){
        for(size_t y = 0; y < DIM; ++y) {
            result.values[y][x] = values[y][x] * other;
        }
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
Matrix<DIM, TYPE> Matrix<DIM, TYPE>::operator+(const Matrix<DIM, TYPE>& other) const {
    Matrix<DIM, TYPE> result;
    for(size_t x = 0; x < DIM; ++x){
        for(size_t y = 0; y < DIM; ++y) {
            result.values[y][x] = values[y][x] + other.values[y][x];
        }
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
Matrix<DIM, TYPE> Matrix<DIM, TYPE>::operator-(const Matrix<DIM, TYPE>& other) const {
    Matrix<DIM, TYPE> result;
    for(size_t x = 0; x < DIM; ++x){
        for(size_t y = 0; y < DIM; ++y) {
            result.values[y][x] = values[y][x] - other.values[y][x];
        }
    }
    return result;
}

template<unsigned int DIM, typename TYPE>
bool Matrix<DIM, TYPE>::operator==(const Matrix<DIM, TYPE> &other) const {
    static constexpr  auto isInRange = [](TYPE a, TYPE b) -> bool{
        constexpr TYPE maxError = 1e-6;
        return a - maxError <= b && a + maxError >= b;
    };
    Matrix<DIM, TYPE> result;
    for(size_t x = 0; x < DIM; ++x){
        for(size_t y = 0; y < DIM; ++y) {
            if(!isInRange(values[y][x], other.values[y][x])){
                return false;
            }
        }
    }
    return true;
}

template<unsigned int DIM, typename TYPE>
bool Matrix<DIM, TYPE>::operator!=(const Matrix<DIM, TYPE> &other) const {
    return !(*this  == other);
}
