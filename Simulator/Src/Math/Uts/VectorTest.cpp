#include <gtest/gtest.h>
#include <Vector.hpp>
#include <Quaternion.hpp>
#include <cmath>

using Vector3d = Vector3<double>;
using Quaterniond = Quaternion<double>;

TEST(VectorTest, ZeroLength){
    const Vector3d zeroVector;
    EXPECT_EQ(zeroVector.length(), 0.);
}

TEST(VectorTest, NonZeroLength){
    const Vector3d vector3d(3., 4., 5.);
    EXPECT_DOUBLE_EQ(vector3d.length(), std::sqrt(50));
}

TEST(VectorTest, NormalizeZeroVector){
    const Vector3d zeroVector;
    EXPECT_EQ(zeroVector.normalized(), std::nullopt);
}

TEST(VectorTest, NormalizeNonZeroVector){
    const Vector3d vector3d(3., 1., -2.);
    const auto result = vector3d.normalized();
    ASSERT_NE(result, std::nullopt);
    const Vector3d resultVector(result.value());

    const double denominator = std::sqrt(14.);
    EXPECT_DOUBLE_EQ(resultVector.x(), vector3d.x() / denominator);
    EXPECT_DOUBLE_EQ(resultVector.y(), vector3d.y() / denominator);
    EXPECT_DOUBLE_EQ(resultVector.z(), vector3d.z() / denominator);
}

TEST(VectorTest, AddTwoVectors){
    const Vector3d first(3., 1., -2.);
    const Vector3d second(0.5, 0, 5.);
    const Vector3d result1 = first + second;
    const Vector3d result2 = second + first;

    EXPECT_EQ(result1, result2);

    EXPECT_DOUBLE_EQ(result1.x(), 3.5);
    EXPECT_DOUBLE_EQ(result1.y(), 1.);
    EXPECT_DOUBLE_EQ(result1.z(), 3.);
}

TEST(VectorTest, SubTwoVectors){
    const Vector3d first(3., 1., -2.);
    const Vector3d second(0.5, 0, 5.);
    const Vector3d result1 = first - second;
    const Vector3d result2 =  -second + first;

    EXPECT_EQ(result1, result2);

    EXPECT_DOUBLE_EQ(result1.x(), 2.5);
    EXPECT_DOUBLE_EQ(result1.y(), 1.);
    EXPECT_DOUBLE_EQ(result1.z(), -7.);
}

TEST(VectorTest, MultiplyByScalar){
    const Vector3d vector3d(3., 1., -2.);
    const Vector3d result = vector3d * 0.75;

    EXPECT_DOUBLE_EQ(result.x(), 2.25);
    EXPECT_DOUBLE_EQ(result.y(), 0.75);
    EXPECT_DOUBLE_EQ(result.z(), -1.5);
}

TEST(VectorTest, RotateDirectionVectorByPitch){
    const Vector3d vector3d(4, 0, 0);
    Quaterniond quaternion(Vector3d(0, 45, 0));
    const Vector3d result = vector3d.rotatedByQuaternion(quaternion);

    EXPECT_DOUBLE_EQ(result.x(), std::sqrt(2) / 2. * 4);
    EXPECT_DOUBLE_EQ(result.y(), 0);
    EXPECT_DOUBLE_EQ(result.z(), -std::sqrt(2) / 2. * 4);
}

TEST(VectorTest, RotateDirectionVectorByPitchAndRoll){
    const Vector3d vector3d(4, 0, 0);
    Quaterniond quaternion(Vector3d(45, 45, 0));
    const Vector3d result = vector3d.rotatedByQuaternion(quaternion);

    EXPECT_NEAR(result.x(), std::sqrt(2) / 2. * 4., 1e-6);
    EXPECT_NEAR(result.y(), 0, 1e-6);
    EXPECT_NEAR(result.z(), -std::sqrt(2) / 2. * 4., 1e-6);
}

TEST(VectorTest, RotateDirectionVectorByPitchAndYaw){
    const Vector3d vector3d(4, 0, 0);
    Quaterniond quaternion(Vector3d(0, 45, 45));
    const Vector3d result = vector3d.rotatedByQuaternion(quaternion);

    EXPECT_NEAR(result.x(), 2., 1e-6);
    EXPECT_NEAR(result.y(), 2., 1e-6);
    EXPECT_NEAR(result.z(), -std::sqrt(2) * 2., 1e-6);
}

TEST(VectorTest, RotateDirectionVectorBy360Degrees){
    const Vector3d vector3d(4, 0, 0);
    Quaterniond quaternion(Vector3d(360, 360, -360));
    const Vector3d result = vector3d.rotatedByQuaternion(quaternion);

    EXPECT_NEAR(result.x(), vector3d.x(), 1e-6);
    EXPECT_NEAR(result.y(), vector3d.y(), 1e-6);
    EXPECT_NEAR(result.z(), vector3d.z(), 1e-6);
}
