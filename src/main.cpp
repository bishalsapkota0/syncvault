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

    return 0;
}