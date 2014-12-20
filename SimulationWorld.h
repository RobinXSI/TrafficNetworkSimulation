#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "Node.h"

class SimulationWorld {
public:
    typedef std::map<Id, Node*> Nodes;
    Nodes nodes;

    void readNodes();
    inline void tokenize(const std::string& str, std::vector<std::string>& tokens) {
        tokens.erase(tokens.begin(), tokens.end());
        tokens.push_back("TRASH");
        std::string buf;
        std::stringstream ss(str);
        while(ss >> buf) {
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

