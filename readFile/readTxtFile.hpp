#include "readFile.hpp"


class readTxtFile : public readFile {
    public:
    readTxtFile(std::string path);

    void read(char delim) override;
};