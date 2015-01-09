#ifndef NODE_H_
#define NODE_H_

#include <vector>

class Link;

typedef double Coordinate;
using Id = long;

class Node {
private:
    Id id;
    Coordinate xx; // EASTING
    Coordinate yy; // NORTHING

    typedef std::vector<Link*> VLinks;
    VLinks outgoingLinks;
    VLinks incomingLinks;

public:
    void setId(Id value);
    Id getId();

    void setXX(Coordinate value);
    Coordinate getXX();

    void setYY(Coordinate value);
    Coordinate  getYY();

    void addOutgoingLink(Link* link);
    Link* getOutgoingLink(int i);
    int countOutgoingLinks();

    void addIncomingLink(Link* link);
    Link* getIncomingLink(int i);
    int countIncomingLinks();


    void randomMoveToLink();
    void move() {
        randomMoveToLink();
    }
};

#endif