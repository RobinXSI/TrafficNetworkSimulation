#include "Link.h"
#include <assert.h>
#include "global.h"

void Link::setId(Id value) { id = value; }
Id Link::getId() { return id; }

void Link::setFromNode(Node* node) { fromNode = node; }
Node* Link::getFromNode() { return fromNode; }

void Link::setToNode(Node* node) { toNode = node; }
Node* Link::getToNode() { return toNode; }

void Link::setLength(Length value) { length = value; }
Length  Link::getLength() { return length; }

void Link::build() {
    int numberOfStreetCells;
    numberOfStreetCells = int(getLength() / CELL_LENGTH);
    for(int i = 0; i < numberOfStreetCells; i++) {
        streetCells.push_back(NULL);
    }
}

void Link::addVehicleToLink(Vehicle* vehicle) {
    assert(streetCells[0] == NULL);
    streetCells[0] = vehicle;
}

Vehicle* Link::firstOnLink() {
    return streetCells.back();
}

void Link::removeFirstOnLink() {
    assert(streetCells.back() != NULL);
    streetCells.back() = NULL;
}

bool Link::hasSpace() {
    return streetCells.front() == NULL;
}


// Traditional Array Syntax
// Should be refactored to C++11
void Link::moveOnLink(int& numberOfVehicles) {
    int last = streetCells.size() - 1;
    for(int i = 0; i < last; i++) {
        Vehicle* vehicle = streetCells[i];
        if(vehicle != NULL) {
            numberOfVehicles++;
            if(streetCells[i + 1] == NULL) {
                streetCells[i + 1] = vehicle;
                streetCells[i] = NULL;
                i++;
                vehicle->setSpeed(CELL_LENGTH);
            } else {
                vehicle->setSpeed(0.0);
            }
        }
    }
}

void Link::move(int& numberOfVehicles) {
    moveOnLink(numberOfVehicles);
    // more here to be added later
}

void Link::writeVehicleFile(Time globalTime) {

    static int first = 1;
    static std::ofstream snapshotFile;
    if(first == 1) {
        first = 0;
        snapshotFile.open(SNAPSHOT_FILE_NAME);
        assert(snapshotFile.is_open());
        snapshotFile << "VEHICLE"
                << '\t' << "TIME"
                << '\t' << "LINK"
                << '\t' << "NODE"
                << '\t' << "LANE"
                << '\t' << "DISTANCE"
                << '\t' << "VELOCITY"
                << '\t' << "VEHTYPE"
                << '\t' << "ACCELER"
                << '\t' << "DRIVER"
                << '\t' << "PASSENGERS"
                << '\t' << "EASTING"
                << '\t' << "NORTHING"
                << '\t' << "ELEVATION"
                << '\t' << "AZIMUTH"
                << '\t' << "USER"
                << std::endl;
    }
    assert(snapshotFile.is_open());

    // write TWO empty lines between time steps:
    static Time lastTimeStep = -1;
    if(lastTimeStep != globalTime) {
        snapshotFile << "\n\n" << std::endl;
        lastTimeStep = globalTime;
    }

    // go through all cells of the link:
    for(int ii = 0; ii < streetCells.size(); ii++) {
        // check if cells have a vehicle on them:
        if(streetCells[ii] != NULL) {
            // get the vehicle and its position on the link:
            Vehicle* theVehicle = streetCells[ii];
            double pos = 7.5 * (ii + 1);
            int lane = 1;
            // calculate geographical coordinates and azimuth:
            Coordinate DX = -fromNode->getXX() + toNode->getXX();
            Coordinate DY = -fromNode->getYY() + toNode->getYY();
            typedef double Angle;
            Angle theta = 0.0;
            if(DX > 0) {
                theta = std::atan(DY / DX);
            } else if(DX < 0){
                theta = PI + std::atan(DY/DX);
            } else {
                if(DY > 0) { theta = PI / 2.0; }
                else { theta = -PI / 2.0; }
            }
            if(theta < 0.0) { theta += 2.0 * PI; }
            double azimuth = theta / (2.0 * PI) * 360;
            Coordinate easting = fromNode->getXX() + cos(theta) * pos + sin(theta) * LANE_WIDTH * lane;
            Coordinate northing = fromNode->getYY() + sin(theta) * pos - cos(theta) * LANE_WIDTH * lane;
            Coordinate elevation = 0.0;
            // write the information to the file:
            snapshotFile << theVehicle->getId()
                    << '\t' << globalTime
                    << '\t' << getId() // link id
                    << '\t' << fromNode->getId()
                    << '\t' << lane
                    << '\t' << pos
                    << '\t' << theVehicle->getSpeed()
                    << '\t' << 1 // vehtype
                    << '\t' << 0.0 // acceleration
                    << '\t' << theVehicle->getId() // driver id
                    << '\t' << 0 // number of passengers
                    << '\t' << easting
                    << '\t' << northing
                    << '\t' << elevation
                    << '\t' << azimuth
                    << '\t' << 0 // user definable field
                    << "\n";




        }
    }


}