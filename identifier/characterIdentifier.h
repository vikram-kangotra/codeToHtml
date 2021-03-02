#ifndef CHARACTER_IDENTIFIER
#define CHARACTER_IDENTIFIER

namespace CharacterIdentifier {

bool isalpha(const char& a)
{
    return (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z');
}

bool isdigit(const char& d)
{
    return d >= '0' && d <= '9';
}

bool isblank(const char& b)
{
    return b == ' ' || b == '\n';
}

bool isDoubleInvertedComma(const char& ic)
{
    return ic == '\"';
}

bool isInvertedComma(const char& ic)
{
    return ic == '\'';
}

bool isSymbol(const char& m)
{
    return m == '#' || m == ':' || m == ';' || m == '&' || m == '.' || m == ',' || m == '!';
}

bool isComparisonOperator(char ch)
{
    return ch == '<' || ch == '>' || ch == '=';
}

bool isArithmeticOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch =='/';
}

bool isOperator(const char& op)
{
    return isComparisonOperator(op) || isArithmeticOperator(op);
}

bool isParenthesis(const char& pa)
{
    return pa == '(' || pa == ')' || pa == '{' || pa == '}' || pa == '[' || pa == ']';
}

bool isWhiteSpaceOrNewLine(const char& wn)
{
    return wn == ' ' || wn == '\n';
}

bool isNewline(const char& nl)
{
    return nl == '\n';
}

}

#endif // CHARACTER_IDENTIFIER
