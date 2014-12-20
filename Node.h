typedef double Coordinate;

class Node {
private:
    Id id;
    Coordinate xx; // EASTING
    Coordinate yy; // NORTHING

    typedef std::vector<Link*> VLinks;
    VLinks outgoingLinks;
    VLinks incomingLinks;

public:
    void setId(Id value) { id = value; }
    Id getId() { return id; }

    void setXX(Coordinate value) { xx = value; }
    Coordinate getXX() { return xx; }

    void setYY(Coordinate value) { yy = value; }
    Coordinate  getYY() { return yy; }

    void addOutgoingLink(Link* link) { outgoingLinks.push_back(link); }
    Link* getOutgoingLink(int i) { return outgoingLinks[i]; }
    int countOutgoingLinks() { return outgoingLinks.size(); }

    void addIncomingLink(Link* link) { incomingLinks.push_back(link); }
    Link* getIncomingLink(int i) { return incomingLinks[i]; }
    int countIncomingLinks() { return incomingLinks.size(); }


    void randomMoveToLink() {
        for(VLinks::iterator ll = incomingLinks.begin(); ll != incomingLinks.end(); ++ll) {
            Link* incomingLink = (Link *) *ll;
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
    void move() {
        randomMoveToLink();
    }
};