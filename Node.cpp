#include <map>
#include "Node.h"
#include "global.h"
#include "Vehicle.h"

void Node::setId(Id value) { id = value; }
Id Node::getId() { return id; }

void Node::setXX(Coordinate value) { xx = value; }
Coordinate Node::getXX() { return xx; }

void Node::setYY(Coordinate value) { yy = value; }
Coordinate Node::getYY() { return yy; }

void Node::addOutgoingLink(Link* link) { outgoingLinks.push_back(link); }
Link* Node::getOutgoingLink(int i) { return outgoingLinks[i]; }
int Node::countOutgoingLinks() { return outgoingLinks.size(); }

void Node::addIncomingLink(Link* link) { incomingLinks.push_back(link); }
Link* Node::getIncomingLink(int i) { return incomingLinks[i]; }
int Node::countIncomingLinks() { return incomingLinks.size(); }

void Node::randomMoveToLink() {

    typedef std::multimap<double, Link*> RandomLinks;
    RandomLinks randomLinks;
    // go through all inLinks, give them a random number, and insert
    // them according to it
    for(VLinks::iterator ll=incomingLinks.begin(); ll != incomingLinks.end(); ++ll) {
        Link* link = *ll;
        randomLinks.insert(std::make_pair(myRand(), link));
    }

    for(RandomLinks::iterator ll = randomLinks.begin(); ll != randomLinks.end(); ++ll) {
        Link* incomingLink = ll->second;
        Vehicle* vehicle = incomingLink->firstOnLink(); // NULL if none
        if(vehicle != NULL) {
            int numberOfOutgoingLinks = outgoingLinks.size();
            int outgoingLinkIdx = int(myRand() * numberOfOutgoingLinks);
            Link* theOutgoingLink = getOutgoingLink(outgoingLinkIdx);
            if(theOutgoingLink->hasSpace()) {
                incomingLink->removeFirstOnLink();
                theOutgoingLink->addVehicleToLink(vehicle);
            }
        }
    }
}