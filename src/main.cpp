#include<iostream>
#include<filesystem>
#include <fstream>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include<unordered_map>
#include<vector>

namespace fs = std::filesystem;

struct Chunk{
    std::string hashData;
    std::size_t chunkSize;
    std::size_t offset;
};


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


    std::vector<Chunk> dataChunks;
    std::size_t offset =0;

    if(fs::exists(p)){
        std::ifstream file(p, std::ios::binary);//read in binary 
        while(file.read(buffer.data(), buffer.size()) || file.gcount()>0){
            std::size_t bytesRead = file.gcount();
            offset+=bytesRead;
            std::string chunkHash = sha256(buffer.data(),bytesRead);
            Chunk c1; 
            c1.hashData = chunkHash;
            c1.chunkSize = bytesRead;
            c1.offset = offset;
            dataChunks.push_back(c1);
            //std::cout<<"Bytes read: "<<bytesRead<<std::endl;
            //std::cout<<buffer.data()<<std::endl;
            //std::cout << sha256(buffer.data(), bytesRead) << std::endl;
        }
    }
    else{
        std::cout<<"Error! File does not exist"<<std::endl;
    }

    std::unordered_map<std::string, int>seen;
    std::size_t savedBytes = 0;
    for(const auto& chunk: dataChunks){
        if(seen.find(chunk.hashData) ==seen.end()){
            seen[chunk.hashData] =1;
        }
        else{
            savedBytes +=chunk.chunkSize;
        }
    }
    
    std::cout << "Total chunks:  " << dataChunks.size() << "\n";
    std::cout << "Unique chunks: " << seen.size() << "\n";
    std::cout << "Bytes saved by dedup: " << savedBytes << "\n";
    


    return 0;
}
