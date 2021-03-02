#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "fsm.h"
#include <list>

class Lexer
{
public:

    Lexer(const std::string& program)
        :   mProgram(program),
            mPosition(0),
            mLine(0),
            mColumn(0),
            mEndOfFile(false) {}

    void process();

    Token getNextToken();

    bool eof() const { return mEndOfFile;}

    Token& operator[](const int& i) {return mTokens[i];}

    int size() const {return mTokens.size();}

    Token* begin() {return &mTokens[0];}
    Token* end() {return &mTokens[size()];}
    const Token* begin() const {return &mTokens[0];}
    const Token* end() const {return &mTokens[size()];}

private:

    void skipWhiteSpacesAndNewLines();
    FSM buildNumberRecogniser();

    Token recogniseBlank();
    Token recogniseString();
    Token recogniseCharacter();
    Token recogniseSymbol();
    Token recogniseIdentifier();
    Token recogniseNumber();
    Token recogniseOperator();
    Token recogniseParenthesis();
    Token recogniseArithmeticOperator();
    Token recogniseComparisonOperator();

private:

    std::string mProgram;
    int mPosition;
    int mLine;
    int mColumn;

    bool mEndOfFile;

    std::vector<Token> mTokens;
};

#endif
