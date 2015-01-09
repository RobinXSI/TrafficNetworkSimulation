#ifndef SIMULATIONWORLD_H_
#define SIMULATIONWORLD_H_

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <assert.h>
#include "Vehicle.h"
#include "Node.h"
#include "Link.h"
#include <fstream>
#include <iostream>

std::string const NODES_FILE_NAME = "/Users/robin/ClionProjects/TrafficNetworkSimulation/TNodes.txt";
std::string const LINKS_FILE_NAME = "/Users/robin/ClionProjects/TrafficNetworkSimulation/TLinks.txt";


class SimulationWorld {
public:
    typedef std::map<Id, std::shared_ptr<Node>> Nodes;
    typedef std::map<Id, std::shared_ptr<Link>> Links;
    Nodes nodes;
    Links links;

    void readNodes();
    void readLinks();

    void simulate(bool& done, Time globalTime);

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

