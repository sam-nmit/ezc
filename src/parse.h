#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "token.h"
#include "util.h"

namespace ezc{

struct FileSearchCondition{
    std::string suffix;
    bool exclusive;
};

class Parser{
    public:
        Parser(Tokenizer* t);
        void ParseFile();
        std::map<std::string,std::string> identifers;


    private:
        Tokenizer * tk;
        

        std::string ParseComplexString();
        bool LastIdentifier(Token* t_out);
        std::vector<FileSearchCondition> ParseFileSearchQuery(std::string s);
        std::string ParseFileSearch();
};

}