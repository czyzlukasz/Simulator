#include <gtest/gtest.h>
#include <PlaneItems/PlaneAirfoil.hpp>
#include <PlaneStatus.hpp>
#include <cmath>

struct PlaneAirfoilTest : public testing::Test{
    const double mass = 3.45;
    const double area = 0.87;
    const Quaterniond wingDirectionForward = Quaterniond(Vector3d(0, 0, 0));
    const Quaterniond wingDirection15Pitch = Quaterniond(Vector3d(0, 15, 0));
    const double sqrt2Over2 = std::sqrt(2) / 2;

    const double dragAt1meterPerSecond = 0.0021315;
    const double liftAt1meterPerSecond = 0.106575;
};

TEST_F(PlaneAirfoilTest, ZeroSpeedNoRotation){
    PlaneAirfoil planeAirfoil({}, {}, mass, area, wingDirectionForward);

    PlaneStatus planeStatus{};
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));

    const auto result = planeAirfoil.calculateResultingForce(planeStatus);
    EXPECT_DOUBLE_EQ(result.x(), 0.);
    EXPECT_DOUBLE_EQ(result.y(), 0.);
    EXPECT_DOUBLE_EQ(result.z(), 9.81 * mass);
}

TEST_F(PlaneAirfoilTest, ZeroSpeed15Pitch){
    PlaneAirfoil planeAirfoil({}, {}, mass, area, wingDirection15Pitch);

    PlaneStatus planeStatus{};
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));

    const auto result = planeAirfoil.calculateResultingForce(planeStatus);
    EXPECT_DOUBLE_EQ(result.x(), 0.);
    EXPECT_DOUBLE_EQ(result.y(), 0.);
    EXPECT_DOUBLE_EQ(result.z(), 9.81 * mass);
}

TEST_F(PlaneAirfoilTest, LowForwardSpeedNoRotation){
    PlaneAirfoil planeAirfoil({}, {}, mass, area, wingDirectionForward);

    PlaneStatus planeStatus{};
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));
    planeStatus.speed = Vector3d(1, 0, 0);

    const auto result = planeAirfoil.calculateResultingForce(planeStatus);
    EXPECT_NEAR(result.x(), -dragAt1meterPerSecond, 1e-4);  // Only drag force
    EXPECT_DOUBLE_EQ(result.y(), 0.);
    EXPECT_NEAR(result.z(), 9.81 * mass - liftAt1meterPerSecond, 1e-4);  // Weight and lift
}

TEST_F(PlaneAirfoilTest, HighForwardSpeedNoRotation){
    PlaneAirfoil planeAirfoil({}, {}, mass, area, wingDirectionForward);

    const double forwardSpeed = 6;
    PlaneStatus planeStatus{};
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));
    planeStatus.speed = Vector3d(forwardSpeed, 0, 0);

    const auto result = planeAirfoil.calculateResultingForce(planeStatus);

    // Lift and drag forces should be proportional to speed squared
    const double forwardSpeedSquared = std::pow(forwardSpeed, 2);
    EXPECT_NEAR(result.x(), -dragAt1meterPerSecond * forwardSpeedSquared, 1e-4);
    EXPECT_DOUBLE_EQ(result.y(), 0.);
    EXPECT_NEAR(result.z(), 9.81 * mass - liftAt1meterPerSecond * forwardSpeedSquared, 1e-4);
}

TEST_F(PlaneAirfoilTest, LowForwardSpeed15Pitch){
    PlaneAirfoil planeAirfoil({}, {}, mass, area, wingDirection15Pitch);

    PlaneStatus planeStatus{};
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));
    planeStatus.speed = Vector3d(1, 0, 0);
    // Based on LUT lift at 15 degrees is 8.5 times higher than at 0 AoA
    const double liftFactor = 8.5;
    // Drag is 4 times higher
    const double dragFactor = 4;

    const auto result = planeAirfoil.calculateResultingForce(planeStatus);
    const Vector3d expectedForces = Vector3d(-dragAt1meterPerSecond * dragFactor, 0, - liftAt1meterPerSecond * liftFactor)
            .rotatedByQuaternion(wingDirection15Pitch) + Vector3d (0, 0, 9.81 * mass);
    EXPECT_NEAR(result.x(), expectedForces.x(), 1e-4);
    EXPECT_DOUBLE_EQ(result.y(), expectedForces.y());
    EXPECT_NEAR(result.z(), expectedForces.z(), 1e-4);
}

TEST_F(PlaneAirfoilTest, LowSideSpeedNoRotation){
    PlaneAirfoil planeAirfoil({}, {}, mass, area, wingDirectionForward);

    PlaneStatus planeStatus{};
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));
    planeStatus.speed = Vector3d(0, 1, 0);

    const auto result = planeAirfoil.calculateResultingForce(planeStatus);
    EXPECT_NEAR(result.x(), 0., 1e-4);  // No drag force
    EXPECT_NEAR(result.y(), 0., 1e-4);
    EXPECT_NEAR(result.z(), 9.81 * mass, 1e-4);  // Only weight
}

TEST_F(PlaneAirfoilTest, LowSpeed45YawNoRotation){
    PlaneAirfoil planeAirfoil({}, {}, mass, area, wingDirectionForward);

    PlaneStatus planeStatus{};
    planeStatus.rotation = Quaterniond(Vector3d(0, 0, 0));
    planeStatus.speed = Vector3d(1, 1, 0);

    const auto result = planeAirfoil.calculateResultingForce(planeStatus);
    EXPECT_NEAR(result.x(), -dragAt1meterPerSecond, 1e-4);
    EXPECT_NEAR(result.y(), 0., 1e-4);
    EXPECT_NEAR(result.z(), 9.81 * mass - liftAt1meterPerSecond, 1e-4);
}

TEST_F(PlaneAirfoilTest, LowForwardSpeed90Roll){
    PlaneAirfoil planeAirfoil({}, {}, mass, area, wingDirectionForward);

    PlaneStatus planeStatus{};
    planeStatus.rotation = Quaterniond(Vector3d(90, 0, 0));
    planeStatus.speed = Vector3d(1, 0, 0);

    const auto result = planeAirfoil.calculateResultingForce(planeStatus);
    EXPECT_NEAR(result.x(), -dragAt1meterPerSecond, 1e-4);
    EXPECT_NEAR(result.y(), liftAt1meterPerSecond, 1e-4);
    EXPECT_NEAR(result.z(), 9.81 * mass, 1e-4);
}