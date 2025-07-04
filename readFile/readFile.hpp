#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class readFile {
    protected:
    std::string line;
    std::ifstream ifs;
    public:

    virtual ~readFile();

    virtual void read(char delim) = 0;
};


