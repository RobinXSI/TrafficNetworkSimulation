#include <map>
#include "Node.h"
#include "Vehicle.h"
#include "Link.h"

void Node::setId(Id value) { id = value; }
Id Node::getId() { return id; }

void Node::setXX(Coordinate value) { xx = value; }
Coordinate Node::getXX() { return xx; }

void Node::setYY(Coordinate value) { yy = value; }
Coordinate Node::getYY() { return yy; }

void Node::addOutgoingLink(std::shared_ptr<Link> link) { outgoingLinks.push_back(link); }
std::shared_ptr<Link> Node::getOutgoingLink(int i) { return outgoingLinks[i]; }
int Node::countOutgoingLinks() { return outgoingLinks.size(); }

void Node::addIncomingLink(std::shared_ptr<Link> link) { incomingLinks.push_back(link); }
std::shared_ptr<Link> Node::getIncomingLink(int i) { return incomingLinks[i]; }
int Node::countIncomingLinks() { return incomingLinks.size(); }

void Node::randomMoveToLink() {

    typedef std::multimap<double, std::shared_ptr<Link>> RandomLinks;
    RandomLinks randomLinks;
    // go through all inLinks, give them a random number, and insert
    // them according to it
    for(VLinks::iterator ll=incomingLinks.begin(); ll != incomingLinks.end(); ++ll) {
        std::shared_ptr<Link> link = *ll;
        randomLinks.insert(std::make_pair(this->myRand(), link));
    }

    for(RandomLinks::iterator ll = randomLinks.begin(); ll != randomLinks.end(); ++ll) {
        std::shared_ptr<Link> incomingLink = ll->second;
        std::shared_ptr<Vehicle> vehicle = incomingLink->firstOnLink(); // NULL if none
        if(vehicle != NULL) {
            int numberOfOutgoingLinks = outgoingLinks.size();
            int outgoingLinkIdx = int(this->myRand() * numberOfOutgoingLinks);
            std::shared_ptr<Link> theOutgoingLink = getOutgoingLink(outgoingLinkIdx);
            if(theOutgoingLink->hasSpace()) {
                incomingLink->removeFirstOnLink();
                theOutgoingLink->addVehicleToLink(vehicle);
            }
        }
    }
}
double Node::myRand() {
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand() / RAND_MAX;
}
