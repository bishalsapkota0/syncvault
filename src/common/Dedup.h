#pragma once
#include <vector>
#include <cstddef>
#include "Chunker.h"

struct DedupStats {
    std::size_t totalChunks  = 0;
    std::size_t uniqueChunks = 0;
    std::size_t savedBytes   = 0;
};

DedupStats computeDedup(const std::vector<Chunk>& chunks);