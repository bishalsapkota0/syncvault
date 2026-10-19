#include<iostream>
#include<filesystem>
namespace fs = std::filesystem;

int main(){
   fs::path p = "test.txt";
   std::cout<<"absollute path:"<<fs::absolute(p)<<std::endl;
    if(fs::exists(p)){
        std::cout<<"File size is:"<<fs::file_size(p)<<std::endl;
        std::cout<<"File exists"<<std::endl;
    }
    else{
        std::cout<<"Error! File does not exist"<<std::endl;
    }

    return 0;
}
