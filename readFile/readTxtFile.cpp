#include "readTxtFile.hpp"


// ensure the ifs is closed
readFile::~readFile() {
    if(this->ifs.is_open()) {
        this->ifs.close();
    }
}

readTxtFile::readTxtFile(std::string path) {
    if(this->ifs.is_open()){
        this->ifs.close();
    }
    this->ifs.open(path,std::ios::binary | std::ios::in);
}


void readTxtFile::read(char delim) {
    std::cout << "from readTxtFile" << std::endl;
    char fileData [785];
    if(this->ifs.is_open()){
        ifs.
        .getline(fileData,785);
        // std::cout << fileData << std::endl;
        std::cout <<ifs.width()<< "\n" ;
        std::cout << (int)delim << std::endl;
        // while (getline(ifs,line)){
        //     std::stringstream ss(line);
        //     std::string token;
        //     while( getline(ss,token,delim)) {
        //         std::cout << token<< " ";
        //     }
        //     std::cout << std::endl;
        // }
        ifs.close();
    } else{
        std::cout << "no file is open" << std::endl;
    }
}

// std::vector<std::string> readTxtFile::read(char delim){
//     std::vector<std::string> result;
//     if(this->ifs.is_open()){
//         while (getline(ifs,line)){
//             std::stringstream ss(line);
//             std::string token;
//             while( getline(ss,token,delim)) {
//                 result.push_back(token);
//             }
//         }
//         ifs.close();
//     }
//     return result;
// }