#include <gtest/gtest.h>
#include <PlaneItems/PlaneEngine.hpp>
#include <PlaneStatus.hpp>
#include <cmath>


struct PlaneEngineTest : public testing::Test{
    const double mass = 3.45;
    const Quaterniond engineDirection45Pitch = Quaterniond(Vector3d(0, 45, 0));
    const double maxThrust = 1.2345;
    static constexpr double sqrt2Over2 = std::sqrt(2) / 2;
};

TEST_F(PlaneEngineTest, ZeroThrustWithoutParameter){
    const PlaneEngine planeEngine({}, {}, mass, engineDirection45Pitch, maxThrust, "Thrust");

    PlaneStatus planeStatus;
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));

    const Vector3d result = planeEngine.calculateResultingForce(planeStatus);
    EXPECT_DOUBLE_EQ(result.x(), 0.);
    EXPECT_DOUBLE_EQ(result.y(), 0.);
    EXPECT_DOUBLE_EQ(result.z(), 9.81 * mass);
}

TEST_F(PlaneEngineTest, ZeroThrustWithParameter){
    const PlaneEngine planeEngine({}, {}, mass, engineDirection45Pitch, maxThrust, "Thrust");

    PlaneStatus planeStatus;
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));
    planeStatus.parameters["Thrust"].emplace<float>(0.f);

    const Vector3d result = planeEngine.calculateResultingForce(planeStatus);
    EXPECT_DOUBLE_EQ(result.x(), 0.);
    EXPECT_DOUBLE_EQ(result.y(), 0.);
    EXPECT_DOUBLE_EQ(result.z(), 9.81 * mass);
}

TEST_F(PlaneEngineTest, MaxThrustWithParameter){
    const PlaneEngine planeEngine({}, {}, mass, engineDirection45Pitch, maxThrust, "Thrust");

    PlaneStatus planeStatus;
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));
    planeStatus.parameters["Thrust"].emplace<float>(1.f);

    const Vector3d result = planeEngine.calculateResultingForce(planeStatus);
    EXPECT_DOUBLE_EQ(result.x(), maxThrust * sqrt2Over2);
    EXPECT_DOUBLE_EQ(result.y(), 0);
    EXPECT_DOUBLE_EQ(result.z(), 9.81 * mass - maxThrust * sqrt2Over2);
}

TEST_F(PlaneEngineTest, HalfThrustWithParameter){
    const PlaneEngine planeEngine({}, {}, mass, engineDirection45Pitch, maxThrust, "Thrust");

    PlaneStatus planeStatus;
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));
    const float thrust = 0.5f;
    planeStatus.parameters["Thrust"].emplace<float>(thrust);

    const Vector3d result = planeEngine.calculateResultingForce(planeStatus);
    EXPECT_DOUBLE_EQ(result.x(), maxThrust * sqrt2Over2 * thrust);
    EXPECT_DOUBLE_EQ(result.y(), 0);
    EXPECT_DOUBLE_EQ(result.z(), 9.81 * mass - maxThrust * sqrt2Over2 * thrust);
}