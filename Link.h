#ifndef LINK_H_
#define LINK_H_

#include <fstream>
#include <complex>
#include <vector>
#include "Node.h"
#include "Vehicle.h"
#include "global.h"

typedef double Length;
typedef double Coordinate;
using Id = long;

class Link {
private:
    Id id;
    Node* fromNode;
    Node* toNode;
    Length length;


    typedef std::vector<Vehicle*> StreetCells;
    StreetCells streetCells;

public:
    void setId(Id value);
    Id getId();

    void setFromNode(Node* node);
    Node* getFromNode();

    void setToNode(Node* node);
    Node* getToNode();

    void setLength(Length value);
    Length  getLength();

    void build();

    void addVehicleToLink(Vehicle* vehicle);

    Vehicle* firstOnLink();

    void removeFirstOnLink();

    bool hasSpace();

    void moveOnLink(int& numberOfVehicles);

    void move(int& numberOfVehicles);

    void writeVehicleFile();

};

#endif