#include<iostream>
#include<filesystem>
#include<chrono>
#include<vector>
#include "common/Chunker.h"
#include "common/Dedup.h"
namespace fs = std::filesystem;
namespace chrono = std::chrono;
int main(int argc, char*argv[]){
    if(argc<2){
        std::cout<<"please provide a file path as argument"<<std::endl;
        return 1;
    }
    fs::path p = argv[1];
    if(!fs::exists(p)){
        std::cout<<"File does not exist: "<<p<<std::endl;   
        return 1;
    }
    else{
        std::cout<<"absolute path: "<<fs::absolute(p)<<std::endl;
        std::cout<<"File exists: "<<p<<std::endl;
    }
    auto start = chrono::steady_clock::now();
    std::vector<Chunk> dataChunks = chunkFile(p);
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration<double>(end - start);
    double second = duration.count();
    std::cout << "Time taken to chunk the file: " << second << " seconds;" << std::endl;
    std::cout << "Number of chunks: " << dataChunks.size() << std::endl;
    auto sizeinMB = fs::file_size(p)/1024.0/1024.0;
    std::cout << "File size: " << sizeinMB << " MB" << std::endl;
    auto throput = sizeinMB / second;;
    std::cout << "Throughput: " << throput << " MB/s" << std::endl;
    DedupStats stats = computeDedup(dataChunks);
    std::cout<< "Total Deduplicated  Chunks: " << stats.totalChunks << std::endl;
    std::cout<< "Total Unique Chunks: " << stats.uniqueChunks << std::endl;
    std::cout<< "Total Saved Bytes: " << stats.savedBytes << std::endl;
    std::cout << "Duplicate chunks: " << stats.totalChunks - stats.uniqueChunks << "\n";


    return 0;

}
