#ifndef KEYWORD_HANDLER_H
#define KEYWORD_HANDLER_H

#include "handler.h"
#include <set>

class KeywordHandler : public Handler
{
public:
    CodeFormat handle(Lexer& lexer, Token token)
    {
        CodeFormat codeFormat;
        codeFormat.styleClass = "code-keyword";
        codeFormat.value = token.getValue();
        return codeFormat;
    }


    bool check(Lexer& lexer, const Token& keyword)
    {
        return mKeywords.find(keyword.getValue()) != mKeywords.end();
    }

private:
    static std::set<std::string> mKeywords;
};

#endif // KEYWORD_HANDLER_H
