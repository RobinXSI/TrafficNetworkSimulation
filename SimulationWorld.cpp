#include "SimulationWorld.h"
#include <fstream>
#include <iostream>

const char* NODES_FILE_NAME = "/Users/robin/ClionProjects/TrafficNetworkSimulation/TNodes.txt";
const char* LINKS_FILE_NAME = "/Users/robin/ClionProjects/TrafficNetworkSimulation/TLinks.txt";

void SimulationWorld::readLinks() {
    std::cout << "\n### entering readLinks ...\n";
    std::ifstream inFile;
    inFile.open(LINKS_FILE_NAME, std::ifstream::in);
    assert(inFile.is_open());
    std::string aString;
    std::vector<std::string> tokens;

    // process header line:
    std::getline(inFile, aString);
    tokenize(aString, tokens);
    assert(tokens[1] == "ID");
    assert(tokens[3] == "NODEA");
    assert(tokens[4] == "NODEB");
    assert(tokens[12] == "LENGTH");

    // main loop:
    while(!inFile.eof()) {
        getline(inFile, aString);
        if (!aString.empty() && isdigit(aString[0]))
            // [[ skip lines with junk (e.g. last line) ]]
        {
            tokenize(aString, tokens);
            Id linkId;
            Id fromNodeId;
            Id toNodeId;
            Length length;
            convert(tokens[1], linkId);
            convert(tokens[3], fromNodeId);
            convert(tokens[4], toNodeId);
            convert(tokens[12], length);

            Link* link = new Link();
            links[linkId] = link;
            link->setId(linkId);

            Node* fromNode = nodes[fromNodeId];
            Node* toNode = nodes[toNodeId];
            assert(fromNode != NULL);
            assert(toNode != NULL);

            link->setFromNode(fromNode);
            link->setToNode(toNode);
            link->setLength(length);
            fromNode->addOutgoingLink(link);
            toNode->addIncomingLink(link);
        }
    }
    std::cout << "nLinks: " << links.size() << "\n";
    std::cout << "## leaving readLinks ...\n\n";



}

void SimulationWorld::readNodes() {
    std::cout << "\n### entering readNodes ...\n";

    std::ifstream inFile;
    inFile.open(NODES_FILE_NAME, std::ifstream::in);
    assert(inFile.is_open());
    std::string aString;
    std::vector<std::string> tokens;

    // process header line:
    std::getline(inFile, aString);
    tokenize(aString, tokens);
    assert(tokens[1] == "ID");
    assert(tokens[2] == "EASTING");
    assert(tokens[3] == "NORTHING");

    // main loop:
    while(!inFile.eof()) {
        getline(inFile, aString);
        if(!aString.empty() && isdigit(aString[0]))
            // [[ skip lines with junk (e.g. last line) ]]
        {
            tokenize(aString, tokens);
            Id nodeId;
            Coordinate xCoordinate;
            Coordinate yCoordinate;
            convert(tokens[1], nodeId);
            convert(tokens[2], xCoordinate);
            convert(tokens[3], yCoordinate);

            // initialize node:
            Node *node = new Node();

            // enter node into node map:
            nodes[nodeId] = node;
            node->setId(nodeId);
            node->setXX(xCoordinate);
            node->setYY(yCoordinate);
        }
    }

    std::cout << "nNodes: " << nodes.size() << "\n";
    std::cout << "## leaving readNodes ...\n\n";
}

