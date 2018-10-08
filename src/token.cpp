#include "token.h"

using namespace ezc;

Tokenizer::Tokenizer(std::ifstream* f){
    this->in_file = f;
    this->tokenIndex = 0;

    Token t;
    while(this->ReadNextToken(&t)){
        this->tokens.push_back(t);
    }
    this->tokens.shrink_to_fit();
}

Tokenizer::~Tokenizer(){
    for(auto t:this->tokens){
        if(t.type != TokenType::NEWLINE){
            free(t.value);
        }
    }
}

bool Tokenizer::Next(Token* t_out){
    if(this->tokenIndex < this->tokens.size()){
        *t_out = this->tokens[tokenIndex++];
        return true;
    }else{
        return false;
    }
}

bool Tokenizer::Previous(Token* t_out, int back){
    if(this->tokenIndex != 0 && (this->tokenIndex-back) < this->tokens.size()){
        *t_out = this->tokens[tokenIndex - back];
        return true;
    }else{
        return false;
    }
}

bool Tokenizer::Peek(Token* t_out){
    if((this->tokenIndex) < this->tokens.size()){
        *t_out = this->tokens[tokenIndex];
        return true;
    }else{
        return false;
    }
}


bool Tokenizer::ReadNextToken(Token* t_out){

    Token t;
    char buff[255];
    int size;

    if(this->in_file->eof()/* || !this->in_file->read(&this->buffer, 1)*/){
        return false;
    }
    char nextValue = this->in_file->peek();
    
    t.value = &this->buffer;
    t.position = this->in_file->tellg();

    switch(nextValue){
        case EOF:
            return false;

        case EZC_NEWLINE:
            this->in_file->read(&this->buffer, 1);
            t.type = TokenType::NEWLINE;
            t.size = 0;
        break;

        case EZC_ASSIGNMENT:
            t.type = TokenType::ASSIGNMENT;
                
            this->in_file->read(&this->buffer, 1);
            t.value = (char*)malloc(2);
                
            t.size = 2;
            *t.value = this->buffer;
            *(t.value + 1) = '\0';

            break;

        case EZC_COMMENT:
            t.type = TokenType::COMMENT;
            size = this->ReadToEndOfLine(&buff[0]);
            t.value = (char*)malloc(size);
            memcpy(t.value, &buff, size);
            break;

        case EZC_EXECUTE:
            t.type = TokenType::EXECUTE;
                
            this->in_file->read(&this->buffer, 1);
            t.value = (char*)malloc(2);
                
            t.size = 2;
            *t.value = this->buffer;
            *(t.value + 1) = '\0';
            break;
        
        default:
            if(EZC_IS_IDENTIFER(nextValue)){

                t.type = TokenType::IDENTIFIER;
                size = this->ReadIdentifer(&buff[0]);
                t.value = (char*)malloc(size);
                memcpy(t.value, &buff, size);

            }else if(EZC_IS_WHITESPACE(nextValue)){
                t.type = TokenType::WHITESPACE;
                t.size = this->ReadWhitespace();

                t.value = (char*)malloc(1);
                *t.value = '\0';
            }else{
                t.type = TokenType::STRING;

                this->in_file->read(&this->buffer, 1);
                t.value = (char*)malloc(2);
                
                t.size = 2;
                *t.value = this->buffer;
                *(t.value + 1) = '\0';
            }   
    }

    *t_out = t;
    return true;
}

int Tokenizer::ReadToEndOfLine(char* c){
    int size = 0;
    while((this->in_file->peek() != EZC_NEWLINE) && this->in_file->read(&this->buffer,1)){
        c[size++] = this->buffer;
    }
    c[size++] = '\0';
    return size;

}

int Tokenizer::ReadWhitespace(){
    int count = 0;
    while(EZC_IS_WHITESPACE(this->in_file->peek())){
        this->in_file->read(&this->buffer, 1);
        count++;
    }
    return count;
}

int Tokenizer::ReadIdentifer(char* c){
    int size = 0;
     while(EZC_IS_IDENTIFER(this->in_file->peek())){
        this->in_file->read(&this->buffer, 1);
        c[size++] = this->buffer;
    }
    c[size++] ='\0';
    return size;

}