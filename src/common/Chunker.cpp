#include "Chunker.h"
#include "Hasher.h"
#include "RollingHash.h"
#include <fstream>

namespace {
    const std::size_t READ_SIZE = 8;   
    const std::size_t MIN_CHUNK = 4;
    const std::size_t MAX_CHUNK = 16;
}

std::vector<Chunk> chunkFile(const std::filesystem::path& p) {
    std::vector<Chunk> chunks;
    std::ifstream file(p, std::ios::binary);
    if (!file) {
        return chunks;  
    }

    std::vector<char> buffer(READ_SIZE);
    std::vector<char> current;   
    RollingHash roller;
    std::size_t offset = 0;

    auto finishChunk = [&]() {
        Chunk c;
        c.hashData  = sha256(current.data(), current.size());
        c.chunkSize = current.size();
        c.offset    = offset;
        chunks.push_back(c);

        offset += current.size();
        current.clear();
    };

    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        std::size_t bytesRead = file.gcount();

        for (std::size_t i = 0; i < bytesRead; i++) {
            roller.add((unsigned char)buffer[i]);
            current.push_back(buffer[i]);

            bool contentCut = current.size() >= MIN_CHUNK && roller.isCutPoint();
            bool forcedCut  = current.size() >= MAX_CHUNK;

            if (contentCut || forcedCut) {
                finishChunk();
            }
        }
    }

    if (!current.empty()) {
        finishChunk();
    }

    return chunks;
}