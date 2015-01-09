#ifndef VEHICLE_H_
#define VEHICLE_H_

using Id = long;

class Vehicle {
private:
    Id id;
    double speed;
public:
    void setId(Id value) { id = value; }
    Id getId() { return id; }
    void setSpeed(double value) { speed = value; }
    double getSpeed() { return speed; }
};

#endif