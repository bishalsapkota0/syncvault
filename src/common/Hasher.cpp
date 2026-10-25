#include "Hasher.h"
#include <openssl/evp.h>
std::string sha256(const char* data, std::size_t length) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength = 0;
    EVP_Digest(data, length, hash, &hashLength, EVP_sha256(), nullptr);
    std::string hex;
    const char* digits = "0123456789abcdef";
    for (unsigned int i = 0; i < hashLength; i++) {
        hex += digits[hash[i] >> 4];
        hex += digits[hash[i] & 0x0F];
    }
    return hex;
}
