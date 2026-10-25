#include "Dedup.h"
#include <unordered_map>
#include <string>

DedupStats computeDedup(const std::vector<Chunk>& chunks) {
    DedupStats stats;
    std::unordered_map<std::string, int> seen;

    for (const auto& chunk : chunks) {
        if (seen.find(chunk.hashData) == seen.end()) {
            seen[chunk.hashData] = 1;         
        }
        else {
            seen[chunk.hashData]++;        
            stats.savedBytes += chunk.chunkSize;
        }
    }

    stats.totalChunks  = chunks.size();
    stats.uniqueChunks = seen.size();
    return stats;
}