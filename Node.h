typedef long Id;
typedef double Coordinate;

class Node {
private:
    Id id;

public:
    void setId(Id value) { id = value; }
    Id getId() { return id; }

private:
    Coordinate xx; // EASTING
public:
    void setXX(Coordinate value) { xx = value; }
    Coordinate getXX() { return xx; }

private:
    Coordinate yy; // NORTHING
public:
    void setYY(Coordinate value) { yy = value; }
    Coordinate  getYY() { return yy; }
};