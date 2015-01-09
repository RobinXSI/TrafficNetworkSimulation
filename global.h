#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cstdlib>
#include <iostream>
#include <ctime>



double myRand() {
    std::srand(std::time(0)); // use current time as seed for random generator
    return std::rand() / RAND_MAX;
}

typedef double Time;
Time globalTime = -1;

const char* NODES_FILE_NAME = "/Users/robin/ClionProjects/TrafficNetworkSimulation/TNodes.txt";
const char* LINKS_FILE_NAME = "/Users/robin/ClionProjects/TrafficNetworkSimulation/TLinks.txt";
const char* SNAPSHOT_FILE_NAME = "/Users/robin/ClionProjects/TrafficNetworkSimulation/output.txt";
const double PI = 3.14;
const double CELL_LENGTH = 7.5;


#endif