typedef double Length;

class Link {
private:
    Id id;
    Node* fromNode;
    Node* toNode;
    Length length;
public:
    void setId(Id value) { id = value; }
    Id getId() { return id; }

    void setFromNode(Node* node) { fromNode = node; }
    Node* getFromNode() { return fromNode; }

    void setToNode(Node* node) { toNode = node; }
    Node* getToNode() { return toNode; }

    void setLength(Length value) { length = value; }
    Length  getLength() { return length; }

};