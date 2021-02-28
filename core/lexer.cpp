#include "lexer.h"
#include <iostream>
#include <string>
#include "characterIdentifier.h"

Token Lexer::getNextToken() {

    if(!mTokens.empty()) {
        Token token = mTokens.front();
        mTokens.pop_front();
        return token;
    }

    if(mPosition >= mProgram.length()) {
        mEndOfFile = true;
        return Token(TokenType::END_OF_INPUT);
    }

    const char& character = mProgram[mPosition];

    if(CharacterIdentifier::isblank(character)) {
        return recogniseBlank();
    }

    if(CharacterIdentifier::isalpha(character)) {
        return recogniseIdentifier();
    }

    if(CharacterIdentifier::isdigit(character)) {
        return recogniseNumber();
    }

    if(CharacterIdentifier::isOperator(character)) {
        return recogniseOperator();
    }

    if(CharacterIdentifier::isParenthesis(character)) {
        return recogniseParenthesis();
    }

    if(CharacterIdentifier::isSymbol(character)) {
        return recogniseSymbol();
    }

    if(CharacterIdentifier::isDoubleInvertedComma(character)) {
        return recogniseString();
    }

    if(CharacterIdentifier::isInvertedComma(character)) {
        return recogniseCharacter();
    }

    std::cout << (int)character << '\n';

    throw std::runtime_error("Unrecognized character " + std::string() + character + " at line " + std::to_string(mLine) + " and column " + std::to_string(mColumn));
}

void Lexer::skipWhiteSpacesAndNewLines() {
    while(mPosition < mProgram.length() && CharacterIdentifier::isWhiteSpaceOrNewLine(mProgram[mPosition])) {
        ++mPosition;

        if(CharacterIdentifier::isNewline(mProgram[mPosition])) {
            ++mLine;
            mColumn = 0;
        } else {
            ++mColumn;
        }
    }
}

Token Lexer::recogniseBlank() {
    char character = mProgram[mPosition];
    ++mPosition;

    switch(character) {
        case ' ':   ++mColumn;
                    return Token(TokenType::SPACE, " ", mLine, mColumn-1);
                    break;

        case '\n': ++mLine;
                    mColumn = 0;
                    return Token(TokenType::NEWLINE, "\n", mLine, mColumn);
                    break;
    }
}

Token Lexer::recogniseString() {
    std::string str = "\"";
    int column = mColumn;
    int position = mPosition + 1;

    while(position < mProgram.length()) {
        char character = mProgram[position];
        ++position;

        str += character;

        if(character == '\"')
            break;

        if(character == '\n')
            ++mLine;
    }

    mPosition += str.length();
    mColumn += str.length();

    return Token(TokenType::STRING, str, mLine, column);
}

Token Lexer::recogniseCharacter() {
    std::string str = "\'";
    int column = mColumn;
    int position = mPosition + 1;

    while(position < mProgram.length()) {
        char character = mProgram[position];
        ++position;

        str += character;

        if(character == '\'')
            break;
    }

    mPosition += str.length();
    mColumn += str.length();

    return Token(TokenType::CHARACTER, str, mLine, column);
}

Token Lexer::recogniseSymbol() {
    char character = mProgram[mPosition];
    ++mPosition;
    ++mColumn;

    switch(character) {
        case '#':   return Token(TokenType::HASH        , "#", mLine, mColumn); break;
        case ':':   return Token(TokenType::COLON       , ":", mLine, mColumn); break;
        case ';':   return Token(TokenType::SEMICOLON   , ";", mLine, mColumn); break;
        case '&':   return Token(TokenType::AMPERSAND   , "&", mLine, mColumn); break;
        case '.':   return Token(TokenType::DOT         , ".", mLine, mColumn); break;
        case ',':   return Token(TokenType::COMMA       , ",", mLine, mColumn); break;
        case '!':   return Token(TokenType::NOT         , "!", mLine, mColumn); break;
    }
}

Token Lexer::recogniseIdentifier() {
    std::string identifier;
    int column = mColumn;
    int position = mPosition;

    while(position < mProgram.length()) {
        char character = mProgram[position];

        if(!(isalpha(character) || isdigit(character) || character == '_')) {
            break;
        }

        identifier += character;
        ++position;
    }

    mPosition += identifier.length();
    mColumn += identifier.length();

    return Token(TokenType::IDENTIFIER, identifier, mLine, column);
}

Token Lexer::recogniseNumber() {
    int column = mColumn;

    FSM fsm = buildNumberRecogniser();

    std::string fsmInput = mProgram.substr(mPosition);

    std::string number = fsm.run(fsmInput);

    if(!number.empty()) {
        mPosition += number.length();
        mColumn += number.length();

        return Token(TokenType::NUMBER, number, mLine, column);
    }

    return Token(TokenType::UNKNOWN);
}

FSM Lexer::buildNumberRecogniser() {
    enum {
        NoNextState,

        Initial,
        Integer,
        BeginNumberWithFractionPart,
        NumberWithFractionPart,
        BeginNumberWithExponent,
        BeginNumberWithSignedExponent,
        NumberWithExponent,
    };

    std::vector<int> states{Initial, Integer, BeginNumberWithFractionPart, NumberWithFractionPart, BeginNumberWithExponent, BeginNumberWithSignedExponent, NumberWithExponent, NoNextState};

    int initialState = Initial;

    std::vector<int> acceptingStates{Integer, NumberWithFractionPart, NumberWithExponent};

    FSM fsm(states, initialState, acceptingStates,
        [](const int& currentState, const char& character)->int{

            switch(currentState) {
                case Initial:
                    if(isdigit(character)) {
                        return Integer;
                    }
                    break;
                case Integer:
                    if(isdigit(character)) {
                        return Integer;
                    }

                    if(character == '.') {
                        return BeginNumberWithFractionPart;
                    }

                    if(tolower(character) == 'e') {
                        return BeginNumberWithExponent;
                    }
                    break;
                case BeginNumberWithFractionPart:
                    if(isdigit(character)) {
                        return NumberWithFractionPart;
                    }
                    break;
                case NumberWithFractionPart:
                    if(isdigit(character)) {
                        return NumberWithFractionPart;
                    }

                    if(tolower(character) == 'e') {
                        return BeginNumberWithExponent;
                    }
                    break;
                case BeginNumberWithExponent:
                    if(character == '+' || character =='-') {
                        return BeginNumberWithSignedExponent;
                    }

                    if(isdigit(character)) {
                        return NumberWithExponent;
                    }
                    break;
                case BeginNumberWithSignedExponent:
                    if(isdigit(character)) {
                        return NumberWithExponent;
                    }
                    break;
                default:
                    break;
            }
            return NoNextState;
        } );

    return fsm;
}

Token Lexer::recogniseParenthesis() {
    int column = mColumn;
    const char& Character = mProgram[mPosition];

    ++mPosition;
    ++mColumn;

    switch(Character) {
        case '(':   return Token(TokenType::LEFT_PARENTHESIS        , "(", mLine, column);   break;
        case ')':   return Token(TokenType::RIGHT_PARENTHESIS       , ")", mLine, column);   break;
        case '{':   return Token(TokenType::LEFT_CURLY_PARENTHESIS  , "{", mLine, column);   break;
        case '}':   return Token(TokenType::RIGHT_CURLY_PARENTHESIS , "}", mLine, column);   break;
        case '[':   return Token(TokenType::LEFT_BOX_PARENTHESIS    , "[", mLine, column);   break;
        case ']':   return Token(TokenType::RIGHT_BOX_PARENTHESIS   , "]", mLine, column);   break;
    }
}

Token Lexer::recogniseOperator() {
    const char& character = mProgram[mPosition];

    if(CharacterIdentifier::isComparisonOperator(character)) {
        return recogniseComparisonOperator();
    }

    if(CharacterIdentifier::isArithmeticOperator(character)) {
        return recogniseArithmeticOperator();
    }

    return Token(TokenType::UNKNOWN);
}

Token Lexer::recogniseComparisonOperator() {
    int position = mPosition;
    int column = mColumn;
    const char& character = mProgram[mPosition];

    char lookahead = position + 1 < mProgram.length() ? mProgram[mPosition + 1] : 0;

    bool isLookaheadEqualSymbol = lookahead != 0 && lookahead == '=';

    ++mPosition;
    ++mColumn;

    if(isLookaheadEqualSymbol) {
        ++mPosition;
        ++mColumn;
    }

    switch(character) {
        case '>':
                return isLookaheadEqualSymbol
                    ? Token(TokenType::GREATER_THAN_OR_EQUAL, ">=", mLine, column)
                    : Token(TokenType::GREATER_THAN, ">", mLine, column);
        case '<':
                return isLookaheadEqualSymbol
                    ? Token(TokenType::LESS_THAN_OR_EQUAL, "<=", mLine, column)
                    : Token(TokenType::LESS_THAN, "<", mLine, column);
        case '=':
                return isLookaheadEqualSymbol
                    ? Token(TokenType::EQUAL, "==", mLine, column)
                    : Token(TokenType::ASSIGN, "=", mLine, column);
        default:
                break;
    }

    return Token(TokenType::UNKNOWN);
}

Token Lexer::recogniseArithmeticOperator() {
    int column = mColumn;
    const char& character = mProgram[mPosition];

    ++mPosition;
    ++mColumn;

    switch(character) {
        case '+':
                return Token(TokenType::PLUS, "+", mLine, column);
        case '-':
                return Token(TokenType::MINUS, "-", mLine, column);
        case '*':
                return Token(TokenType::MULT, "*", mLine, column);
        case '/':
                return Token(TokenType::DIV, "/", mLine, column);
        default:
                break;
    }

    return Token(TokenType::UNKNOWN);
}
