#include "htmlConverter.h"

std::set<std::string> HtmlConverter::mKeywords = {
    "auto"  ,   "break" ,   "case"    , "char"  ,   "const"     ,   "continue"  ,   "default"   ,   "do"    ,
    "double",   "else"  ,   "enum"    , "extern",   "float"     ,   "for"       ,   "goto"      ,   "if"    ,
    "int"   ,   "long" 	,   "register", "return",   "short"     ,   "signed"    , 	"sizeof"    ,   "static",
    "struct",  	"switch", 	"typedef" , "union" ,   "unsigned"  ,   "void"      ,   "volatile"  ,    "while"
};

HtmlConverter::HtmlConverter(Lexer lexer)
:   CodeConverter(lexer)
{
    code +=
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

void HtmlConverter::handle()
{
    for(Token token = getNextToken(); !mLexer.eof(); token = getNextToken()) {
        CodeFormat codeFormat = identifyCodeFormat(token);
        if(codeFormat.styleClass.empty()) {
            code += token.getValue();
        } else {
            addToHtml(codeFormat);
        }
    }
}

void HtmlConverter::handleHtmlPrintables(Token& token)
{
    char character = token.getValue()[0];
    switch(character) {
        case '<': token = Token(token.getType(), "&lt;", token.getLine(), token.getColumn()); break;
        case '>': token = Token(token.getType(), "&gt;", token.getLine(), token.getColumn()); break;
    }
}

Token HtmlConverter::getNextToken()
{
    Token token = mLexer.getNextToken();
    handleHtmlPrintables(token);
    return token;
}

CodeFormat HtmlConverter::handleComment(const Token& token)
{
    CodeFormat codeFormat;
    Token nextToken = getNextToken();

    switch(nextToken.getType()) {
        //  Single line comment
        case TokenType::DIV: {
                                codeFormat.styleClass = "code-comment";
                                std::string value = token.getValue() + nextToken.getValue();
                                while((nextToken = getNextToken()).getType() != TokenType::NEWLINE) {
                                    value += nextToken.getValue();
                                }
                                codeFormat.value = value;
                                mLexer.putBack(nextToken);
                            }
                                break;
        // Multi line comment
        case TokenType::MULT: {
                                codeFormat.styleClass = "code-comment";
                                std::string value = token.getValue() + nextToken.getValue();
                                while(!mLexer.eof()) {
                                    nextToken = getNextToken();
                                    value += nextToken.getValue();
                                    if(nextToken.getType() == TokenType::MULT) {
                                        nextToken = getNextToken();
                                        if(nextToken.getType() == TokenType::DIV) {
                                            value += nextToken.getValue();
                                            break;
                                        }
                                        mLexer.putBack(nextToken);
                                    }
                                }
                                codeFormat.value = value;
                            }
                                break;
        default:            mLexer.putBack(nextToken);
    }

    return codeFormat;
}

CodeFormat HtmlConverter::handleMeta(const Token& token)
{
    CodeFormat codeFormat;
    codeFormat.styleClass = "code-meta";
    std::string value = token.getValue();
    Token nextToken;
    while((nextToken = getNextToken()).getType() != TokenType::NEWLINE) {
        value += nextToken.getValue();
    }
    codeFormat.value = value;
    mLexer.putBack(nextToken);

    return codeFormat;
}

CodeFormat HtmlConverter::identifyCodeFormat(const Token& token)
{
    CodeFormat codeFormat;

    if(isKeyword(token.getValue())) {
        codeFormat.styleClass = "code-keyword";
        codeFormat.value = token.getValue();
    } else {
        switch(token.getType()) {
            case TokenType::STRING: {
                                        codeFormat.styleClass = "code-string";
                                        codeFormat.value = token.getValue();
                                    }
                                    break;

            case TokenType::DIV:    codeFormat = handleComment(token);
                                    break;

            case TokenType::HASH:   codeFormat = handleMeta(token);
                                    break;
        }
    }

    return codeFormat;
}

void HtmlConverter::addToHtml(const CodeFormat& codeFormat)
{
    code += R"(<span class=")";
    code += codeFormat.styleClass;
    code += R"(">)";
    code += codeFormat.value;
    code += R"(</span>)";
}
