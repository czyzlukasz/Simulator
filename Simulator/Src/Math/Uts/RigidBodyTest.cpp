#include <gtest/gtest.h>
#include <RigidBody.hpp>

TEST(RigidBodyTest, PureTranslation){
    const double tickLength = 1/60.;
    const Vector3<double> force(12., 13., -2.);

    RigidBody<double> rigidBody;
    rigidBody.mass = 123.45;
    rigidBody.momentOfInertia = {1., 1., 1.};

    IterationData<double> iterationData;
    iterationData.setIterationLength(tickLength);
    // Apply force directly to the center of mass
    iterationData.addActingForce(force, {0., 0., 0.});

    EXPECT_TRUE(rigidBody.iterate(iterationData));

    const Vector3<double> expectedResult = force * tickLength * tickLength / rigidBody.mass;
    EXPECT_DOUBLE_EQ(rigidBody.position.x(), expectedResult.x());
    EXPECT_DOUBLE_EQ(rigidBody.position.y(), expectedResult.y());
    EXPECT_DOUBLE_EQ(rigidBody.position.z(), expectedResult.z());

    EXPECT_EQ(rigidBody.angularVelocity, Vector3<double>(0., 0., 0.));
}

TEST(RigidBodyTest, PureRotation){
    const double tickLength = 1/60.;
    const Vector3<double> force(10., 0., 0.);

    RigidBody<double> rigidBody;
    rigidBody.mass = 123.45;
    rigidBody.momentOfInertia = {3., 3., 3.};
    rigidBody.rotation = Quaternion(Vector3<double>(0., 0., 0.));

    IterationData<double> iterationData;
    iterationData.setIterationLength(tickLength);
    // Apply force two meters to the right of the center of mass
    iterationData.addActingForce(force, {0., 2., 0.});

    EXPECT_TRUE(rigidBody.iterate(iterationData));

    const double expectedResult = -force.x() / rigidBody.momentOfInertia.z() * tickLength * tickLength * 2.;
    const Vector3<double> result = rigidBody.rotation.toEulerAngles();
    EXPECT_DOUBLE_EQ(result.x(), 0.);
    EXPECT_DOUBLE_EQ(result.y(), 0.);
    EXPECT_DOUBLE_EQ(result.z(), expectedResult);
}

TEST(RigidBodyTest, InitialRotationWithoutAnyForce){
    const double tickLength = 4.;
    RigidBody<double> rigidBody;
    rigidBody.mass = 1;
    rigidBody.momentOfInertia = {3., 3., 3.};
    rigidBody.rotation = Quaternion(Vector3<double>(0., 0., 0.));
    rigidBody.angularVelocity = {1., 0.1, -2.};

    IterationData<double> iterationData;
    iterationData.setIterationLength(tickLength);

    EXPECT_TRUE(rigidBody.iterate(iterationData));
    const Vector3<double> result = rigidBody.rotation.toEulerAngles();

    EXPECT_DOUBLE_EQ(result.x(), 4.);
    EXPECT_DOUBLE_EQ(result.y(), 0.4);
    EXPECT_DOUBLE_EQ(result.z(), -8.);
}