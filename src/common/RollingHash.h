#pragma once
#include <deque>
#include <cstddef>
#include <cstdint>

struct RollingHash {
    static constexpr std::size_t   WINDOW  = 4;
    static constexpr std::uint64_t BASE    = 31;
    static constexpr std::uint64_t MOD     = 1000000007;
    static constexpr std::uint64_t DIVISOR = 8;

    std::deque<unsigned char> window;
    std::uint64_t hash = 0;
    std::uint64_t highPower = 1;

    RollingHash();               
    void add(unsigned char b);
    bool isCutPoint() const;
};
