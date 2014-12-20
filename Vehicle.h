class Vehicle {
private:
    Id id;
    double speed;
public:
    void setId(Id value) { id = value; }
    Id getId() { return id; }
    void setSpeed(double value) { speed = value; }
};