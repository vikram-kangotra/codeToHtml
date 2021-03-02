#ifndef CHARACTER_IDENTIFIER
#define CHARACTER_IDENTIFIER

namespace CharacterIdentifier {

inline bool isalpha(const char& a)
{
    return (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z');
}

inline bool isdigit(const char& d)
{
    return d >= '0' && d <= '9';
}

inline bool isblank(const char& b)
{
    return b == ' ' || b == '\n';
}

inline bool isQuotation(const char& ic)
{
    return ic == '\"';
}

inline bool isApostrophe(const char& ic)
{
    return ic == '\'';
}

inline bool isSymbol(const char& m)
{
    return m == '#' || m == ':' || m == ';' || m == '&' || m == '|' || m == '.' || m == ',' || m == '!';
}

inline bool isComparisonOperator(char ch)
{
    return ch == '<' || ch == '>' || ch == '=';
}

inline bool isArithmeticOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch =='/';
}

inline bool isOperator(const char& op)
{
    return isComparisonOperator(op) || isArithmeticOperator(op);
}

inline bool isParenthesis(const char& pa)
{
    return pa == '(' || pa == ')' || pa == '{' || pa == '}' || pa == '[' || pa == ']';
}

inline bool isWhiteSpaceOrNewLine(const char& wn)
{
    return wn == ' ' || wn == '\n';
}

inline bool isNewline(const char& nl)
{
    return nl == '\n';
}

}

#endif // CHARACTER_IDENTIFIER
