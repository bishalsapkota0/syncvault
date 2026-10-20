#include<iostream>
#include<filesystem>
#include <fstream>
#include <openssl/ssl.h>

namespace fs = std::filesystem;

#include<vector>
const std::size_t CHUNK_SIZE = 8;
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


int main(){
    std::vector<char> buffer(CHUNK_SIZE);
   fs::path p = "test.txt";
   
   std::cout<<"absollute path:"<<fs::absolute(p)<<std::endl;

    if(fs::exists(p)){
        std::ifstream file(p, std::ios::binary);
        while(file.read(buffer.data(), buffer.size()) || file.gcount()>0){
            std::size_t bytesRead = file.gcount();
            std::cout<<"Bytes read: "<<bytesRead<<std::endl;
            std::cout<<buffer.data()<<std::endl;
            std::cout << sha256(buffer.data(), bytesRead) << std::endl;
        }
    }
    else{
        std::cout<<"Error! File does not exist"<<std::endl;
    }

    return 0;
}
