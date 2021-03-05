#ifndef HTML_CONVERTER
#define HTML_CONVERTER

#include "lexer.h"
#include "commentHandler.h"
#include "metaHandler.h"
#include "handlerPicker.h"
#include <set>

class HtmlConverter
{
public:
    HtmlConverter(const Lexer& lexer);

    std::string convert();

private:
    Lexer mLexer;
    std::string mCode;

    HandlerPicker mHandlerPicker;

private:
    void handle();
    void addToHtml(CodeFormat& codeFormat);

    void handleHtmlPrintables(std::string& htmlValue);
};

#endif // HTML_CONVERTER
