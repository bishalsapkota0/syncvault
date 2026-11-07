#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include "common/RollingHash.h"
#include "common/Hasher.h"
#include "common/Chunker.h"
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    if(argc<3){
        std::cout<<"please provide a file path as argument"<<std::endl;
        return 1;
    }
    std::string command = argv[1];
    if(command != "upload"){
        std::cout<<"Unknown command: Pleaes upload your file with upload command"<<command<<std::endl;
        return 1;
    }
    fs::path p = argv[2];
    if(!fs::exists(p)){
        std::cout<<"File does not exist: "<<p<<std::endl;
        return 1;
    }
    
    std::cout << "absolute path: " << fs::absolute(p) << std::endl;
    std::size_t offset = 0;
    std::vector<Chunk> dataChunks = chunkFile(p);

    for (const auto& c : dataChunks) {
                std::cout << "Current Offset " << c.offset
              << " |Chunk Size" << c.chunkSize
              << " |Chunk Hash String : " << c.hashData.substr(0, 12) << "...\n";
    }

    return 0;
}