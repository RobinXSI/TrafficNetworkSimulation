// Forward Declaration because of Circular Dependency
class Link;

typedef long Id;
typedef double Coordinate;

class Node {
private:
    Id id;
    Coordinate xx; // EASTING
    Coordinate yy; // NORTHING

    typedef std::vector<Link*> VLinks;
    VLinks outLinks;
    VLinks inLinks;

public:
    void setId(Id value) { id = value; }
    Id getId() { return id; }

    void setXX(Coordinate value) { xx = value; }
    Coordinate getXX() { return xx; }

    void setYY(Coordinate value) { yy = value; }
    Coordinate  getYY() { return yy; }

    void addOutLink(Link* link) { outLinks.push_back(link); }
    Link* getOutLink(int i) { return outLinks[i]; }
    int countOutLinks() { return outLinks.size(); }

    void addInLink(Link* link) { inLinks.push_back(link); }
    Link* getInLink(int i) { return inLinks[i]; }
    int countInLinks() { return inLinks.size(); }
};