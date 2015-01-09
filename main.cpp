
#include "SimulationWorld.h"


int main() {
    SimulationWorld simulationWorld = SimulationWorld();
    simulationWorld.readNodes();
    simulationWorld.readLinks();

    for(SimulationWorld::Links::iterator ll = simulationWorld.links.begin(); ll != simulationWorld.links.end(); ++ll) {
        std::shared_ptr<Link> link = ll->second;
        link->build();
    }

    // insert some vehicles as explained above
    Id count = 0;
    for(SimulationWorld::Links::iterator ll=simulationWorld.links.begin(); ll != simulationWorld.links.end(); ++ll) {
        std::shared_ptr<Link> link = ll->second;
        auto vehicle = std::make_shared<Vehicle>();

        vehicle->setId(count);
        count++;
        link->addVehicleToLink(vehicle);
    }




    // time iteration:
    int simulationStartTime = 1;

    Time globalTime;

    for(globalTime = simulationStartTime; globalTime < 99999; globalTime++) {
        bool done = false;
        simulationWorld.simulate(done, globalTime);
        if(done) break;
    }



    return 0;
}