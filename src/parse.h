#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "token.h"

namespace ezc{

class Parser{
    public:
        Parser(Tokenizer* t);
        void ParseFile();
        std::map<std::string,std::string> identifers;

    private:
        Tokenizer * tk;
        

        std::string ParseComplexString();
        bool LastIdentifier(Token* t_out);
};

}