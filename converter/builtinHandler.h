#ifndef BUILT_IN_HANDLER_H
#define BUILT_IN_HANDLER_H

#include "handler.h"

class BuiltinHandler : public Handler
{
public:
    CodeFormat handle(Lexer& lexer, Token token)
    {
        CodeFormat codeFormat;
        codeFormat.styleClass = "code-builtin";
        codeFormat.value = token.getValue();
        return codeFormat;
    }

    bool check(Lexer& lexer, const Token& builtin) { return mBuiltins.find(builtin.getValue()) != mBuiltins.end();}

private:
    static std::set<std::string> mBuiltins;
};

#endif // BUILT_IN_HANDLER_H
