#include <Simulator.hpp>
#include <cmath>

Simulator::Simulator() : planeItems(), planeStatus(), rigidBody(), isInitialized(false), timePointSinceStart(){
    rigidBody.rotation = Quaterniond(Vector3d{0, 0, 0});
}

void Simulator::initialize(TimePoint startTimePoint) {
    for(const auto& planeItem : planeItems){
        const double mass = planeItem->getMass();
        const Vector3d& momentOfInertia = planeItem->getMomentOfInertia();
        const double distanceFromCenterOfMass = planeItem->getDostanceFromCenterOfMass().length();

        // Calculate moment of inertia relative to center of mass using Steiner's theorem
        const Vector3d momentOfInertiaOfItem = momentOfInertia + std::pow(distanceFromCenterOfMass, 2) * mass;

        // Add plane item to rigid body
        rigidBody.mass += mass;
        rigidBody.momentOfInertia = rigidBody.momentOfInertia + momentOfInertiaOfItem;

        // Initialize simulator only if there is at least one plane item
        isInitialized = true;
    }
    if(isInitialized){
        timePointSinceStart = startTimePoint;
    }
}

bool Simulator::iterate(TimePoint newTimePoint) {
    if(!isInitialized){
        return false;
    }

    if(newTimePoint <= timePointSinceStart){
        return false;
    }
    const double iterationLength = std::chrono::duration_cast<std::chrono::microseconds>(newTimePoint - timePointSinceStart).count() / 1.e6;
    IterationData<double> iterationData;
    iterationData.setIterationLength(iterationLength);

    // Iterate over all plane items adding theirs forces to main rigid body
    for(const auto& planeItem : planeItems){
        iterationData.addActingForce(planeItem->calculateResultingForce(planeStatus), planeItem->getDostanceFromCenterOfMass());
    }

    // Calculate plane status of current iteration
    if(rigidBody.iterate(iterationData)) {
        // Copy data from rigid body to plane status
        planeStatus.rotation = rigidBody.rotation;
        planeStatus.speed = rigidBody.velocity;
        planeStatus.position = rigidBody.position;

        timePointSinceStart = newTimePoint;
        return true;
    }

    return false;
}

const PlaneStatus &Simulator::getPlaneStatus() const {
    return planeStatus;
}
