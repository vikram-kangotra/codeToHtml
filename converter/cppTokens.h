#include "keywordHandler.h"
#include "builtinHandler.h"

std::set<std::string> KeywordHandler::mKeywords = {
    "auto",
    "break",
    "case",
    "char",
    "class",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "namespace",
    "private",
    "protected",
    "public",
    "register",
    "return",
    "runtime_error"
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "using",
    "void",
    "volatile",
    "while"
};

std::set<std::string> BuiltinHandler::mBuiltins =  {
    "cerr",
    "cin",
    "cout",
    "exception",
    "list",
    "map",
    "std",
    "string",
    "vector",
};