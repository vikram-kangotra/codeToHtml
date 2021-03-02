#ifndef CODE_CONVERTER
#define CODE_CONVERTER

#include "lexer.h"
#include <vector>

class CodeConverter {
public:
    CodeConverter(const Lexer& lexer)
        :   mLexer(lexer) {
        mLexer.process();
    }

    virtual std::string convert() = 0;

    virtual ~CodeConverter() {}

protected:
    Lexer mLexer;
    std::string code;
};

#endif // CODE_CONVERTER
