#include "SimulationWorld.h"
#include <fstream>
#include <iostream>
#include <assert.h>

void SimulationWorld::readNodes() {
    std::cout << "\n### entering readNodes ...\n";

    std::ifstream inFile;
    inFile.open("/Users/robin/ClionProjects/TrafficNetworkSimulation/TNodes.txt", std::ifstream::in);
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
    std::cout << "## leaving readNodes...\n\n";



}

