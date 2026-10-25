#pragma once
#include <string>
#include <vector>
#include <cstddef>
#include <filesystem>

struct Chunk {
    std::string hashData;
    std::size_t chunkSize;
    std::size_t offset;  
};
std::vector<Chunk> chunkFile(const std::filesystem::path& p);