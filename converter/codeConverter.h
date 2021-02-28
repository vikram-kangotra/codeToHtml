#ifndef CODE_CONVERTER
#define CODE_CONVERTER

#include "lexer.h"

class CodeConverter {
public:
    CodeConverter(Lexer lexer)
    :   mLexer(lexer) {}

    virtual std::string convert() = 0;

    virtual ~CodeConverter() {}
protected:
    std::string code;
    Lexer mLexer;
};

#endif // CODE_CONVERTER
