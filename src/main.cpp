#include<iostream>
#include<filesystem>
#include <fstream>
namespace fs = std::filesystem;
#include<vector>
const std::size_t CHUNK_SIZE = 8;


int main(){
    std::vector<char> buffer(CHUNK_SIZE);
   fs::path p = "test.txt";
   
   std::cout<<"absollute path:"<<fs::absolute(p)<<std::endl;
    if(fs::exists(p)){

        std::cout<<"File size is:"<<fs::file_size(p)<<std::endl;
        std::ifstream file(p, std::ios::binary);
        file.read(buffer.data(),buffer.size());
        std::size_t bytesRead = file.gcount(); 
        std::cout<<"Bytes read:"<<bytesRead<<std::endl;
        std::string line;
        while(std::getline(file, line)){
            std::cout<<line<<std::endl;
        }
        std::cout<<"File exists"<<std::endl;
    }
    else{
        std::cout<<"Error! File does not exist"<<std::endl;
    }

    return 0;
}
