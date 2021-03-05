#ifndef COMMENT_HANDLER_H
#define COMMENT_HANDLER_H

#include "handler.h"
#include "codeFormat.h"
#include <iostream>

class CommentHandler : public Handler
{
public:

    CodeFormat handle(Lexer& lexer, Token token)
    {
        CodeFormat codeFormat;
        codeFormat.styleClass = "code-comment";

        bool isComment = false;

        while(true) {
            codeFormat.value += token.getValue();
            if(isComment)
                break;
            isComment = isCommentEnd(lexer, token);
            token = lexer.getNextToken();
        }

        return codeFormat;
    }

    bool check(Lexer& lexer, const Token& token)
    {
        const Token nextToken = lexer.peek();
        return (token.is(TokenType::DIV)) and
           (nextToken.is(TokenType::DIV) or nextToken.is(TokenType::MULT));
    }

private:

    bool isCommentEnd(Lexer& lexer, const Token& token)
    {
        const Token nextToken = lexer.peek();
        return (token.is(TokenType::NEWLINE)) or
            (token.is(TokenType::MULT) and nextToken.is(TokenType::DIV));
    }
};

#endif // COMMENT_HANDLER_H

