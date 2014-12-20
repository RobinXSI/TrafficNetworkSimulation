

// Forward Declaration because of Circular Dependency
class Node;

typedef double Length;

const double CELL_LENGTH = 7.5;


class Link {
private:
    Id id;
    Node* fromNode;
    Node* toNode;
    Length length;

    typedef std::vector<Vehicle*> StreetCells;
    StreetCells streetCells;

public:
    void setId(Id value) { id = value; }
    Id getId() { return id; }

    void setFromNode(Node* node) { fromNode = node; }
    Node* getFromNode() { return fromNode; }

    void setToNode(Node* node) { toNode = node; }
    Node* getToNode() { return toNode; }

    void setLength(Length value) { length = value; }
    Length  getLength() { return length; }

    void build() {
        int numberOfStreetCells;
        numberOfStreetCells = int(getLength() / CELL_LENGTH);
        for(int i = 0; i < numberOfStreetCells; i++) {
            streetCells.push_back(NULL);
        }
    }

    void addVehicleToLink(Vehicle* vehicle) {
        assert(streetCells[0] == NULL);
        streetCells[0] = vehicle;
    }

    Vehicle* firstOnLink() {
        return streetCells.back();
    }

    void removeFirstOnLink() {
        assert(streetCells.back() != NULL);
        streetCells.back() = NULL;
    }

    bool hasSpace() {
        return streetCells.front() == NULL;
    }


    // Traditional Array Syntax
    // Should be refactored to C++11
    void moveOnLink(int& numberOfVehicles) {
        int last = streetCells.size() - 1;
        for(int i = 0; i < last; i++) {
            Vehicle* vehicle = streetCells[i];
            if(vehicle != NULL) {
                numberOfVehicles++;
                if(streetCells[i + 1] == NULL) {
                    streetCells[i + 1] = vehicle;
                    streetCells[i] = NULL;
                    i++;
                    vehicle->setSpeed(CELL_LENGTH);
                } else {
                    vehicle->setSpeed(0.0);
                }
            }
        }
    }

    void move(int& numberOfVehicles) {
        moveOnLink(numberOfVehicles);
        // more here to be added later
    }

};