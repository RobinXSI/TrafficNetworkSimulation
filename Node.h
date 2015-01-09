#ifndef NODE_H_
#define NODE_H_

#include <vector>

class Link;

using Coordinate = double;
using Id = long;

class Node {
private:
    Id id;
    Coordinate xx; // EASTING
    Coordinate yy; // NORTHING

    using VLinks = std::vector<std::shared_ptr<Link>>;

    VLinks outgoingLinks;
    VLinks incomingLinks;

public:
    void setId(Id value);
    Id getId();

    void setXX(Coordinate value);
    Coordinate getXX();

    void setYY(Coordinate value);
    Coordinate  getYY();

    void addOutgoingLink(std::shared_ptr<Link> link);
    std::shared_ptr<Link> getOutgoingLink(int i);
    int countOutgoingLinks();

    void addIncomingLink(std::shared_ptr<Link> link);
    std::shared_ptr<Link> getIncomingLink(int i);
    int countIncomingLinks();


    void randomMoveToLink();
    void move() {
        randomMoveToLink();
    }
    double myRand();
};

#endif