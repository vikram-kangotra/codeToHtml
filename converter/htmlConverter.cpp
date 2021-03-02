#include "htmlConverter.h"
#include "cppTokens.h"

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

    for(auto& token: mLexer) {
        handleHtmlPrintables(token);
    }
}

void HtmlConverter::handleHtmlPrintables(Token& token)
{
    char character = token.getValue()[0];
    switch(character) {
    case '<':
        token = Token(token.getType(), "&lt;", token.getLine(), token.getColumn());
        break;
    case '>':
        token = Token(token.getType(), "&gt;", token.getLine(), token.getColumn());
        break;
    }
}

void HtmlConverter::handle()
{
    if(mTokenIndex >= mLexer.size())
        return;

    CodeFormat codeFormat = identifyCodeFormat();
    addToHtml(codeFormat);
    handle();
}

HtmlConverter::CodeFormat HtmlConverter::identifyCodeFormat()
{
    CodeFormat codeFormat;

    const Token& token = mLexer[mTokenIndex];
    codeFormat.value = token.getValue();

    if(isKeyword(token)) {
        codeFormat.styleClass = "code-keyword";
        codeFormat.value = token.getValue();
    } else if(isBuiltin(token)) {
        codeFormat.styleClass = "code-built-in";
        codeFormat.value = token.getValue();
    } else if(isCommentStart(token)) {
        codeFormat = handleComment();
    } else if(isFunction(token)) {
        codeFormat.styleClass = "code-function";
        codeFormat.value = token.getValue();
    } else if(isMeta(token)) {
        codeFormat = handleMeta();
    } else {

        switch(token.getType()) {
        case TokenType::STRING: {
            codeFormat.styleClass = "code-string";
            codeFormat.value = token.getValue();
            break;
        }
        case TokenType::CHARACTER:  {
            codeFormat.styleClass = "code-charater";
            codeFormat.value = token.getValue();
            break;
        }
        case TokenType::NUMBER: {
            codeFormat.styleClass = "code-number";
            codeFormat.value = token.getValue();
            break;
        }
        default:
            break;
        }
    }

    ++mTokenIndex;
    return codeFormat;
}

bool HtmlConverter::isCommentStart(const Token& token)
{
    const TokenType nextTokenType = mLexer[mTokenIndex+1].getType();
    return (token.getType() == TokenType::DIV) &&
           ((nextTokenType == TokenType::DIV) || (nextTokenType == TokenType::MULT));
}

HtmlConverter::CodeFormat HtmlConverter::handleComment()
{
    CodeFormat codeFormat;
    codeFormat.styleClass = "code-comment";

    while(true) {
        const Token& token = mLexer[mTokenIndex];
        codeFormat.value += token.getValue();
        ++mTokenIndex;
        if(isCommentEnd(token)) {
            codeFormat.value += mLexer[mTokenIndex].getValue();
            break;
        }
    }

    return codeFormat;
}

bool HtmlConverter::isCommentEnd(const Token& token)
{
    const TokenType nextTokenType = mLexer[mTokenIndex+1].getType();
    return (token.getType() == TokenType::NEWLINE) ||
           ((token.getType() == TokenType::MULT) && (nextTokenType == TokenType::DIV));
}

bool HtmlConverter::isFunction(const Token& token)
{
    return (mLexer[mTokenIndex+1].getType() == TokenType::LEFT_PARENTHESIS);
}

bool HtmlConverter::isMeta(const Token& token)
{
    return token.getType() == TokenType::HASH;
}

HtmlConverter::CodeFormat HtmlConverter::handleMeta()
{
    CodeFormat codeFormat;
    codeFormat.styleClass = "code-meta";

    while(true) {
        const Token& token = mLexer[mTokenIndex];
        codeFormat.value += token.getValue();
        if(token.getType() == TokenType::NEWLINE)
            break;
        ++mTokenIndex;
    }

    return codeFormat;
}

void HtmlConverter::addToHtml(const CodeFormat& codeFormat)
{
    if(codeFormat.styleClass.empty()) {
        code += codeFormat.value;
    } else {
        code += R"(<span class=")";
        code += codeFormat.styleClass;
        code += R"(">)";
        code += codeFormat.value;
        code += R"(</span>)";
    }
}
