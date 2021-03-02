#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
    IDENTIFIER,
    NUMBER,
    STRING,
    CHARACTER,

    SPACE,
    NEWLINE,

    HASH,
    COLON,
    SEMICOLON,
    AMPERSAND,
    DOT,
    COMMA,
    NOT,

    PLUS,
    MINUS,
    MULT,
    DIV,

    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN,
    LESS_THAN_OR_EQUAL,
    EQUAL,

    ASSIGN,

    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_BRACES,
    RIGHT_BRACES,
    LEFT_BRACKET,
    RIGHT_BRACKET,

    END_OF_INPUT,

    UNKNOWN
};

class Token
{
public:
    Token(const TokenType& type = TokenType::UNKNOWN, const std::string& value = "", const int& line = 0, const int& column = 0)
        :   mType(type),
            mValue(value),
            mLine(line),
            mColumn(column) {}

    const TokenType& getType() const
    {
        return mType;
    }
    const std::string& getValue() const
    {
        return mValue;
    }
    const int& getLine() const
    {
        return mLine;
    }
    const int& getColumn() const
    {
        return mColumn;
    }

    std::string getTypeStr() const
    {
        switch(mType) {
        case TokenType::IDENTIFIER:
            return "Identifier";
            break;
        case TokenType::NUMBER:
            return "Number";
            break;
        case TokenType::PLUS:
            return "Plus";
            break;
        case TokenType::MINUS:
            return "Minus";
            break;
        case TokenType::MULT:
            return "Mult";
            break;
        case TokenType::DIV:
            return "Div";
            break;
        case TokenType::GREATER_THAN:
            return "Grater Than";
            break;
        case TokenType::GREATER_THAN_OR_EQUAL:
            return "Greater Than Or Equal";
            break;
        case TokenType::LESS_THAN:
            return "Less Than";
            break;
        case TokenType::LESS_THAN_OR_EQUAL:
            return "Less Than Or Equal";
            break;
        case TokenType::EQUAL:
            return "Equal";
            break;
        case TokenType::ASSIGN:
            return "Assign";
            break;
        case TokenType::LEFT_PARENTHESIS:
            return "Left ParenThesis";
            break;
        case TokenType::RIGHT_PARENTHESIS:
            return "RightParenthesis";
            break;
        case TokenType::END_OF_INPUT:
            return "End Of Input";
            break;
        case TokenType::STRING:
            return "String";
            break;
        case TokenType::CHARACTER:
            return "Character";
            break;
        case TokenType::SPACE:
            return "Space";
            break;
        case TokenType::NEWLINE:
            return "Newline";
            break;
        case TokenType::HASH:
            return "Hash";
            break;
        case TokenType::COLON:
            return "Colon";
            break;
        case TokenType::SEMICOLON:
            return "SemiColon";
            break;
        case TokenType::AMPERSAND:
            return "Ampersand";
            break;
        case TokenType::DOT:
            return "Dot";
            break;
        case TokenType::COMMA:
            return "Comma";
            break;
        case TokenType::NOT:
            return "Not";
            break;
        case TokenType::LEFT_BRACES:
            return "Left Braces";
            break;
        case TokenType::RIGHT_BRACES:
            return "Right Braces";
            break;
        case TokenType::LEFT_BRACKET:
            return "Left Bracket";
            break;
        case TokenType::RIGHT_BRACKET:
            return "Right Bracket";
            break;
        case TokenType::UNKNOWN:
            return "Unkown";
            break;
        }
        return "Unknown";
    }

private:

    TokenType mType;
    std::string mValue;
    int mLine;
    int mColumn;
};

#endif
