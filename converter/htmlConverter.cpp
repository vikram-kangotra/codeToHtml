#include "htmlConverter.h"
#include "cppTokens.h"

HtmlConverter::HtmlConverter(const Lexer& lexer)
    :   mLexer(lexer)
{
    mCode +=
        R"(<!DOCTPYE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Code</title>
        <link rel="stylesheet" href="style.css">
    </head>
    <body>
        <pre style="max-height: 600px;"><code>)";
}

std::string HtmlConverter::convert()
{
    handle();

    mCode += R"(</code></pre>
    </body>
</html>
)";
    return mCode;
}

void HtmlConverter::handle()
{
    while(!mLexer.eof()) {
        Token token = mLexer.getNextToken();
        Handler* handler = mHandlerPicker.get(mLexer, token);
        if(handler == nullptr)
            mCode += token.getValue();
        else {
            CodeFormat codeFormat = handler->handle(mLexer, token);
            addToHtml(codeFormat);
        }
    }
}

void HtmlConverter::addToHtml(CodeFormat& codeFormat)
{
    handleHtmlPrintables(codeFormat.value);

    if(codeFormat.styleClass.empty()) {
        mCode += codeFormat.value;
    } else {
        mCode += R"(<span class=")";
        mCode += codeFormat.styleClass;
        mCode += R"(">)";
        mCode += codeFormat.value;
        mCode += R"(</span>)";
    }
}

void HtmlConverter::handleHtmlPrintables(std::string& htmlValue)
{
    std::string temp;
    for(size_t i=0; i<htmlValue.size(); ++i) {
        switch(htmlValue[i]) {
        case '<':
            temp += "&lt;";
            break;
        case '>':
            temp += "&gt;";
            break;
        default:
            temp += htmlValue[i];
        }
    }
    htmlValue = temp;
}
