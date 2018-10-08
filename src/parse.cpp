#include "parse.h"

using namespace ezc;


Parser::Parser(Tokenizer* tk){
    this->tk = tk;
}


std::string Parser::ParseComplexString(){
    std::string s;

    ezc::Token t;
    ezc::Token temp_t;
    
    while(this->tk->Next(&t) && t.type != TokenType::NEWLINE && t.type != TokenType::COMMENT){
        if(t.type == TokenType::WHITESPACE){
            if(s.size() != 0){
                for(int i = 0; i < t.size; i++){
                    s.append(" ");
                }
            }
            continue;
        }
        if(t.type == TokenType::STRING){
            if(*t.value == EZC_EXCAPE){
                this->tk->Next(&t);
                s.append(t.value);
            }else if(*t.value == EZC_IDENTIFER){
                this->tk->Next(&t);
                s.append(this->identifers[t.value]);
            }else{
                s.append(t.value);
            }
        }else if(t.type == EZC_FILESEARCH){
            std::cout << "FINISH ME!" << std::endl;
        
        }else{
            s.append(t.value);
        }
    }
    return s;
}

bool Parser::LastIdentifier(Token *t_out){
    for(int i = 2; this->tk->Previous(t_out, i); i++){
        if(t_out->type == TokenType::IDENTIFIER){
            return true;
        }

        if (t_out->type != TokenType::WHITESPACE){
            break;
        }
    }
    return false;
}

void Parser::ParseFile(){
    ezc::Token t;
    ezc::Token temp_t;

     while(this->tk->Next(&t)){
        switch(t.type){
            case ezc::TokenType::ASSIGNMENT:
                if(!this->LastIdentifier(&temp_t) || !(temp_t.type == ezc::TokenType::IDENTIFIER)){
                    std::cout << t.position << ": " << "Assignment must be used with a identifer." << temp_t.value << std::endl;
                    return;
                }else{
                    this->identifers[temp_t.value] = this->ParseComplexString();
                }
            break;
        }
    }

}