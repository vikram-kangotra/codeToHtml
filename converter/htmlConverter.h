#ifndef HTML_CONVERTER
#define HTML_CONVERTER

#include "lexer.h"
#include "codeConverter.h"
#include <set>

class HtmlConverter : public CodeConverter
{
public:
    HtmlConverter(Lexer lexer);

    std::string convert()
    {
        handle();

        code += R"(</code></pre>
    </body>
</html>
)";
        return code;
    }
private:
    static std::set<std::string> mKeywords;
    static std::set<std::string> mBuiltins;

    int mTokenIndex = 0;

    struct CodeFormat {
        std::string styleClass;
        std::string value;
    };

private:
    bool isKeyword(const Token& keyword) { return mKeywords.find(keyword.getValue()) != mKeywords.end();}
    bool isBuiltin(const Token& builtin) { return mBuiltins.find(builtin.getValue()) != mBuiltins.end();}

    bool isCommentStart(const Token& token);
    bool isCommentEnd(const Token& token);
    bool isFunction(const Token& token);
    bool isMeta(const Token& token);

private:
    void handle();
    void addToHtml(const CodeFormat& codeFormat);

    void handleHtmlPrintables(Token& token);
    CodeFormat identifyCodeFormat();
    CodeFormat handleComment();
    CodeFormat handleMeta();
};

#endif // HTML_CONVERTER
