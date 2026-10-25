#include "RollingHash.h"

void RollingHash::add(unsigned char b) {
    window.push_back(b);
    sum += b;

    if (window.size() > WINDOW) {
        sum -= window.front();
        window.pop_front();
    }
}

bool RollingHash::isCutPoint() const {
    return window.size() == WINDOW && sum % DIVISOR == 0;
}