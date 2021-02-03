#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <vector>
#include <memory>
#include <chrono>
#include <PlaneItem.hpp>
#include <PlaneStatus.hpp>
#include <RigidBody.hpp>

struct Simulator {
    friend struct SimulatorTest;
    Simulator();

    template<typename TYPE, typename... Args>
    Simulator& addPlaneItem(Args... args){
        static_assert(std::is_base_of_v<PlaneItem, TYPE>, "Only PlaneItem is allowed");
        planeItems.push_back(std::make_unique<TYPE>(std::forward<Args>(args)...));

        return *this;
    }

    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::milliseconds>;
    // This function shall be called after all items are added and before first iterate function is called
    void initialize(TimePoint startTimePoint);
    // Iteration function that advances simulation to given time
    [[nodiscard]] bool iterate(TimePoint newTimePoint);
    [[nodiscard]] const PlaneStatus& getPlaneStatus() const;

private:
    std::vector<std::unique_ptr<PlaneItem>> planeItems;
    PlaneStatus planeStatus;
    RigidBody<double> rigidBody;
    bool isInitialized;
    TimePoint timePointSinceStart;
};


#endif //SIMULATOR_HPP
