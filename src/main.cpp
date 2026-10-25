#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include "common/RollingHash.h"
#include "common/Hasher.h"
#include "common/Chunker.h"
namespace fs = std::filesystem;

int main() {
    fs::path p = "test.txt";
    std::cout << "absolute path: " << fs::absolute(p) << std::endl;
    std::size_t offset = 0;
    std::vector<Chunk> dataChunks = chunkFile(p);

    for (const auto& c : dataChunks) {
                std::cout << "Current Offset " << c.offset
              << " |Chunk Size" << c.chunkSize
              << " |Chunk Hash String : " << c.hashData.substr(0, 12) << "...\n";
    }
    
    std::unordered_map<std::string, int> seen;
    std::size_t savedBytes = 0;
    for (const auto& chunk : dataChunks) {
        if (seen.find(chunk.hashData) == seen.end()) {
            seen[chunk.hashData] = 1;
        }
        else {
            seen[chunk.hashData]++;
            savedBytes += chunk.chunkSize;
        }
    }
    std::cout << "Total chunks:  " << dataChunks.size() << "\n";
    std::cout << "Unique chunks: " << seen.size() << "\n";
    std::cout << "Bytes saved by dedup: " << savedBytes << "\n";

    return 0;
}