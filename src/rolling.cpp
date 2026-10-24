#include <iostream>
#include <string>

int main() {
    const std::size_t WINDOW = 4;
    //std::string text = "This line repeats.";
    unsigned int sum = 0;
    std::string text = "AAA This line repeats. BB This line repeats. C This line repeats.";
std::string current;   // the chunk being built

for (std::size_t i = 0; i < text.size(); i++) {
    sum += (unsigned char)text[i];
    if (i >= WINDOW) {
        sum -= (unsigned char)text[i - WINDOW];
    }

    current += text[i];

    if (i >= WINDOW && sum % 8 == 0) {     // the cut rule
        std::cout << "[" << current << "]\n";
        current.clear();                    // start a new chunk
    }
}
std::cout << "[" << current << "]\n";       // last leftover chunk

return 0;
}