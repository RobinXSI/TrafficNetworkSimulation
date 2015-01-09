#ifndef LINK_H_
#define LINK_H_

#include <fstream>
#include <complex>
#include <vector>
#include "Node.h"
#include "Vehicle.h"
#include "global.h"

using Length = double;
using Coordinate = double;
using Id = long;

std::string const SNAPSHOT_FILE_NAME = "/Users/robin/ClionProjects/TrafficNetworkSimulation/output.txt";

class Link {
private:
    Id id;
    std::shared_ptr<Node> fromNode;
    std::shared_ptr<Node> toNode;
    Length length;


    using StreetCells = std::vector<std::shared_ptr<Vehicle>>;

    StreetCells streetCells;

public:
    void setId(Id value);
    Id getId();

    void setFromNode(std::shared_ptr<Node> node);
    std::shared_ptr<Node> getFromNode();

    void setToNode(std::shared_ptr<Node> node);
    std::shared_ptr<Node> getToNode();

    void setLength(Length value);
    Length  getLength();

    void build();

    void addVehicleToLink(std::shared_ptr<Vehicle> vehicle);

    std::shared_ptr<Vehicle> firstOnLink();

    void removeFirstOnLink();

    bool hasSpace();

    void moveOnLink(int& numberOfVehicles);

    void move(int& numberOfVehicles);

    void writeVehicleFile(Time globalTime);

};

#endif