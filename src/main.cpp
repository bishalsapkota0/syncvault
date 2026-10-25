#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <deque>

namespace fs = std::filesystem;

struct Chunk {
    std::string hashData;
    std::size_t chunkSize;
    std::size_t offset;   // where this chunk starts in the file
};

const std::size_t CHUNK_SIZE = 8;   // how many bytes we read from the file at a time
const std::size_t WINDOW     = 4;   // rolling hash looks at the last 4 bytes
const std::size_t MIN_CHUNK  = 4;   // never cut before a chunk has 4 bytes
const std::size_t MAX_CHUNK  = 16;  // always cut when a chunk reaches 16 bytes
const unsigned int DIVISOR   = 8;   // cut when window sum % 8 == 0

// Rolling hash: 
//fixed size sliding window algorithm 
struct RollingHash {
    std::deque<unsigned char> window;
    unsigned int sum = 0;

    void add(unsigned char b) {
        window.push_back(b);
        sum += b;
        if (window.size() > WINDOW) {
            sum -= window.front();
            window.pop_front();
        }
    }
    // true when the window is full and the content says "cut here"
    bool isCutPoint() const {
        return window.size() == WINDOW && sum % DIVISOR == 0;
    }
};

int main() {
    std::vector<char> buffer(CHUNK_SIZE);
    fs::path p = "test.txt";
    std::cout << "absolute path: " << fs::absolute(p) << std::endl;

    std::vector<Chunk> dataChunks;
    std::size_t offset = 0;

    if (fs::exists(p)) {
        std::ifstream file(p, std::ios::binary);   // read in binary

        std::vector<char> current;   
        RollingHash roller;

        
        auto finishChunk = [&]() {
            Chunk c1;
            c1.hashData  = sha256(current.data(), current.size());
            c1.chunkSize = current.size();
            c1.offset    = offset;
            dataChunks.push_back(c1);

            std::cout << "offset " << c1.offset << " size " << c1.chunkSize
                      << " [" << std::string(current.begin(), current.end()) << "]\n";

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

        // whatever is left at the end of the file is the last chunk
        if (!current.empty()) {
            finishChunk();
        }
    }
    else {
        std::cout << "Error! File does not exist" << std::endl;
        return 1;
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