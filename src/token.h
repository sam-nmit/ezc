#pragma once

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>



namespace ezc{
#define EZC_IDENTIFER_MAX_SIZE 255


#define EZC_WHITESPACE  ' '
#define EZC_ASSIGNMENT  '='
#define EZC_COMMENT     '#'
#define EZC_EXECUTE     '>'
#define EZC_NEWLINE     '\n'
#define EZC_EXCAPE      '\\'
#define EZC_IDENTIFER   '$'
#define EZC_FILESEARCH  '{'
#define EZC_FILESEARCH_END  '}'

#define EZC_IS_IDENTIFER(x) ((x > 'A' && x < 'Z') || (x > 'a' && x < 'z') || (x == '_'))
#define EZC_IS_WHITESPACE(x) (x == EZC_WHITESPACE || x == '\r')


enum TokenType {
    WHITESPACE,
    NEWLINE,
    STRING,
    IDENTIFIER,
    ASSIGNMENT,
    COMMENT,
    EXECUTE,
};

struct Token{
    int position;
    TokenType type;
    char* value;
    int size;
};

class Tokenizer{

    public:
        Tokenizer(std::ifstream* f);
        ~Tokenizer();
        bool Next(Token* t_out);
        bool Previous(Token *t_out, int back);
        bool Peek(Token *t_out);

    private:
        int tokenIndex;
        char buffer;
        std::ifstream* in_file;
        std::vector<Token> tokens;

        bool ReadNextToken(Token* t_out);
        int ReadWhitespace();
        int ReadIdentifer(char* c);
        int ReadString(char* c);
        int ReadToEndOfLine(char* c);
};


}