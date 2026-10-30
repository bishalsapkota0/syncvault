#include "RollingHash.h"

// Runs once when a RollingHash is created: highPower = 31^3 % MOD
RollingHash::RollingHash() {
    for (std::size_t i = 0; i < WINDOW - 1; i++) {
        highPower = (highPower * BASE) % MOD;
    }
}

void RollingHash::add(unsigned char b) {
    if (window.size() == WINDOW) {
        unsigned char old = window.front();
        window.pop_front();
        hash = (hash + MOD - (old * highPower) % MOD) % MOD;
    }

    hash = (hash * BASE) % MOD;

    // (iv) add the new byte
    hash = (hash + b) % MOD;
    window.push_back(b);
}

bool RollingHash::isCutPoint() const {
    return window.size() == WINDOW && hash % DIVISOR == 0;
}

