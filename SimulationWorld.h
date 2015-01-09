#ifndef SIMULATIONWORLD_H_
#define SIMULATIONWORLD_H_

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "global.h"
#include <assert.h>
#include "Vehicle.h"
#include "Node.h"
#include "Link.h"
#include <fstream>
#include <iostream>



class SimulationWorld {
public:
    typedef std::map<Id, Node*> Nodes;
    typedef std::map<Id, Link*> Links;
    Nodes nodes;
    Links links;

    void readNodes() {
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
    void readLinks() {
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

    void simulate(bool& done) {
        int numberOfVehicles = 0;
        // links movement:
        for(Links::iterator ll = links.begin(); ll != links.end(); ++ll) {
            Link* theLink = ll->second;
            theLink->move(numberOfVehicles);
        }
        //intersection movement:
        for(Nodes::iterator nn = nodes.begin(); nn != nodes.end(); ++nn) {
            Node *theNode = nn->second;
            theNode->move();
        }
        // output
        int skip = 60;
        if(long(globalTime) % skip == 0) {
            for(Links::iterator ll = links.begin(); ll != links.end(); ++ll) {
                Link* theLink = ll->second;
                theLink->writeVehicleFile();
            }
        }

        if(long(globalTime) % 1000 == 0) {
            std::cout << "Step: " << globalTime << " NVehs: " << numberOfVehicles << std::endl;
        }

        done = false;
        if(numberOfVehicles == 0) {
            done = true;
        }

    }

    inline void tokenize(const std::string& str, std::vector<std::string>& tokens) {
        tokens.erase(tokens.begin(), tokens.end());
        tokens.push_back("TRASH");
        std::string buf;
        std::stringstream ss(str);
        while (ss >> buf) {
            tokens.push_back(buf);
        }
    }

    inline void convert(const std::string& str, int& ii) {
        ii = atoi(str.c_str());
    }
    inline void convert(const std::string& str, long& ii) {
        ii = atol(str.c_str());
    }
    inline void convert(const std::string& str, double& dd) {
        dd = atof(str.c_str());
    }
};

#endif

