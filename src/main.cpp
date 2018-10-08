#include <iostream>
#include <fstream>

#include "token.h"
#include "parse.h"
#include "util.h"

#define EZC_FILE_NAME "_"

int main(){
    
    std::ifstream f(EZC_FILE_NAME);

    if(!f.is_open()){
        std::cout << "Failed to find EZC configuration file \"" << EZC_FILE_NAME << "\" in working directory." << std::endl;
        return 0;
    }


    ezc::Tokenizer tokenreader(&f);

    ezc::Parser p(&tokenreader);
    p.ParseFile();

    for(auto v:p.identifers){
        std::cout << v.first << ": " << v.second << std::endl;
    }

    std::vector<std::string> files = ezc::getfiles();

    for(auto file:files){
        std::cout << file << std::endl;
    }

    return 0;
}