#ifndef META_HANDLER_H
#define META_HANDLER_H

#include "handler.h"
#include "codeFormat.h"
#include <iostream>

class MetaHandler : public Handler
{
public:

    CodeFormat handle(Lexer& lexer, Token token)
    {
        CodeFormat codeFormat;
        codeFormat.styleClass = "code-meta";

        while(true) {
            codeFormat.value += token.getValue();
            token = lexer.peek();
            if(token.is(TokenType::NEWLINE))
                break;
            token = lexer.getNextToken();
        }

        return codeFormat;
    }

    bool check(Lexer& lexer, const Token& token)
    {
        return token.is(TokenType::HASH);
    }
};

#endif // META_HANDLER_H

