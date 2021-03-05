#ifndef HANDLER_H
#define HANDLER_H

#include "codeFormat.h"

class Handler
{
public:
    virtual CodeFormat handle(Lexer& lexer, Token token) = 0;
    virtual bool check(Lexer& lexer, const Token& token) = 0;
    virtual ~Handler() {}
};

#endif // HANDLER_H
