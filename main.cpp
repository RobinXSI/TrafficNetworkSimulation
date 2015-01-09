
#include "SimulationWorld.h"

int main() {
    SimulationWorld simulationWorld;
    simulationWorld.readNodes();
    simulationWorld.readLinks();

    for(SimulationWorld::Links::iterator ll = simulationWorld.links.begin(); ll != simulationWorld.links.end(); ++ll) {
        Link* link = ll->second;
        link->build();
    }

    // insert some vehicles as explained above
    Id count = 0;
    for(SimulationWorld::Links::iterator ll=simulationWorld.links.begin(); ll != simulationWorld.links.end(); ++ll) {
        Link* link = ll->second;
        Vehicle* vehicle = new Vehicle;
        vehicle->setId(count);
        count++;
        link->addVehicleToLink(vehicle);
    }

    // time iteration:
    int simulationStartTime = 1;
    for(globalTime = simulationStartTime; globalTime < 99999; globalTime++) {
        bool done = false;
        simulationWorld.simulate(done);
        if(done) break;
    }



    return 0;
}