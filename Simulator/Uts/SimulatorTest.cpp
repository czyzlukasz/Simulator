#include <gtest/gtest.h>
#include <Simulator.hpp>
#include "PlaneItemMock.hpp"

using namespace std::literals;

struct SimulatorTest : public testing::Test{
    void SetUp() override{
        simulatorPtr = std::make_unique<Simulator>();
    }

    void TearDown() override{
        simulatorPtr.reset();
    }

    Simulator& simulator(){
        return *simulatorPtr;
    }

    const auto& planeItems() const{
        return simulatorPtr->planeItems;
    }
    using TimePoint = Simulator::TimePoint;
    TimePoint now() const{
        return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    }
private:
    std::unique_ptr<Simulator> simulatorPtr;
};

TEST_F(SimulatorTest, RunSimulationWithoutInitialization){
    simulator().addPlaneItem<PlaneItemMock>(Vector3d{1, 1, 1}, Vector3d{2, 2, 2}, 3.);
    const TimePoint timePoint = now();

    EXPECT_FALSE(simulator().iterate(timePoint));
}

TEST_F(SimulatorTest, RunSimulationWithInitializationWithoutPlaneItems){
    simulator().initialize(now());
    const TimePoint timePoint = now() + 10s;

    EXPECT_FALSE(simulator().iterate(timePoint));
}

TEST_F(SimulatorTest, RunSimulationWithZeroDurationTime){
    simulator().addPlaneItem<PlaneItemMock>(Vector3d{1, 1, 1}, Vector3d{2, 2, 2}, 3.);
    const TimePoint timePoint = now();
    simulator().initialize(timePoint);

    EXPECT_FALSE(simulator().iterate(timePoint));
}

TEST_F(SimulatorTest, RunSimulationWithWrongPlaneItemData){
    simulator().addPlaneItem<PlaneItemMock>(Vector3d{}, Vector3d{}, 0.);
    const TimePoint timePoint = now();
    simulator().initialize(timePoint);

    EXPECT_CALL(*static_cast<PlaneItemMock*>(planeItems().at(0).get()), calculateResultingForce(testing::_));
    EXPECT_FALSE(simulator().iterate(timePoint + 50ms));
}

TEST_F(SimulatorTest, RunSimulationWithProperInitalization){
    simulator().addPlaneItem<PlaneItemMock>(Vector3d{1, 1, 1}, Vector3d{2, 2, 2}, 3.);
    const TimePoint timePoint = now();
    simulator().initialize(timePoint);


    EXPECT_CALL(*dynamic_cast<PlaneItemMock*>(planeItems().at(0).get()), calculateResultingForce(testing::_));
    EXPECT_TRUE(simulator().iterate(timePoint + 50ms));
}

TEST_F(SimulatorTest, RunSimulationWithOnePlaneItem){
    const double mass = 3.456;
    const Vector3d distanceFromCom(0, 2, 0);
    const Vector3d momentOfInertia(5, 6, 7);
    const auto tickLength = 50ms;

    simulator().addPlaneItem<PlaneItemMock>(distanceFromCom, momentOfInertia, mass);
    const TimePoint timePoint = now();
    simulator().initialize(timePoint);

    const Vector3d resultingForce(0, 0, -5);
    EXPECT_CALL(*dynamic_cast<PlaneItemMock*>(planeItems().at(0).get()), calculateResultingForce(testing::_))
        .WillOnce(testing::Return(resultingForce));
    EXPECT_TRUE(simulator().iterate(timePoint + tickLength));

    const double torqueAroundXAxis = distanceFromCom.y() * resultingForce.z();
    // Calculate moment of inertia of plane item using Steiner's theorem
    const double angularAccelerationAroundXAxis = torqueAroundXAxis / (momentOfInertia.x() + std::pow(distanceFromCom.length(), 2) * mass);
    const double rollAngle = angularAccelerationAroundXAxis * std::pow(tickLength.count() / 1.e3, 2);
    EXPECT_DOUBLE_EQ(simulator().getPlaneStatus().rotation.toEulerAngles().x(), rollAngle);
}

TEST_F(SimulatorTest, RunSimulationWithTwoPlaneItems){
    const double mass = 3.456;
    const Vector3d distanceFromCom(0, 2, 0);
    const Vector3d momentOfInertia(5, 6, 7);
    const auto tickLength = 50ms;

    simulator().addPlaneItem<PlaneItemMock>(distanceFromCom, momentOfInertia, mass)
               .addPlaneItem<PlaneItemMock>(-distanceFromCom, momentOfInertia, mass);
    const TimePoint timePoint = now();
    simulator().initialize(timePoint);

    const Vector3d resultingForce(0, 0, -5);
    EXPECT_CALL(*dynamic_cast<PlaneItemMock*>(planeItems().at(0).get()), calculateResultingForce(testing::_))
            .WillOnce(testing::Return(resultingForce));
    EXPECT_CALL(*dynamic_cast<PlaneItemMock*>(planeItems().at(1).get()), calculateResultingForce(testing::_))
            .WillOnce(testing::Return(resultingForce));
    EXPECT_TRUE(simulator().iterate(timePoint + tickLength));

    const double torqueAroundXAxis = distanceFromCom.y() * resultingForce.z();
    // Calculate moment of inertia of plane item using Steiner's theorem
    const double angularAccelerationAroundXAxis = torqueAroundXAxis / (momentOfInertia.x() + std::pow(distanceFromCom.length(), 2) * mass);
    const double rollAngle = angularAccelerationAroundXAxis * std::pow(tickLength.count() / 1.e3, 2);
    EXPECT_DOUBLE_EQ(simulator().getPlaneStatus().rotation.toEulerAngles().x(), 0.);
}