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

        Token getNextToken();
        void putBack(const Token& token) { mTokens.push_back(token);}

        bool eof() { return mEndOfFile;}

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

        std::list<Token> mTokens;
};

#endif
