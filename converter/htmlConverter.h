#ifndef HTML_CONVERTER
#define HTML_CONVERTER

#include "lexer.h"
#include "codeConverter.h"
#include <set>

struct CodeFormat {
    std::string styleClass;
    std::string value;
};

class HtmlConverter : public CodeConverter{
public:
    HtmlConverter(Lexer lexer);

    std::string convert() {

        handle();

        code += R"(</code></pre>
    </body>
</html>
)";
        return code;
    }

    bool isKeyword(const std::string& keyword) { return mKeywords.find(keyword) != mKeywords.end();}
private:
    static std::set<std::string> mKeywords;

private:
    void handle();
    void addToHtml(const CodeFormat& codeFormat);
    CodeFormat identifyCodeFormat(const Token& token);
    void handleHtmlPrintables(Token& token);

    Token getNextToken();
    CodeFormat handleComment(const Token& token);
    CodeFormat handleMeta(const Token& token);
};

#endif // HTML_CONVERTER
