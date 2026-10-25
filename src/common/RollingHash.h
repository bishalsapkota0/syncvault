#pragma once
#include <deque>
#include <cstddef>

struct RollingHash {
    static constexpr std::size_t WINDOW  = 4;  
    static constexpr unsigned int DIVISOR = 8;  

    std::deque<unsigned char> window;
    unsigned int sum = 0;

    void add(unsigned char b);   
    bool isCutPoint() const;     
};
