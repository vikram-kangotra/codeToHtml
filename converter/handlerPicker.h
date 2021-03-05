#ifndef HANDLER_PICKER_H
#define HANDLER_PICKER_H

#include "handler.h"
#include "keywordHandler.h"
#include "builtinHandler.h"
#include <memory>
#include <vector>

class HandlerPicker
{
public:
    HandlerPicker()
    {
        mHandlers.push_back(std::make_unique<CommentHandler>());
        mHandlers.push_back(std::make_unique<MetaHandler>());
        mHandlers.push_back(std::make_unique<KeywordHandler>());
        mHandlers.push_back(std::make_unique<BuiltinHandler>());
    }

    Handler* get(Lexer& lexer, const Token& token)
    {
        for(auto& handler: mHandlers) {
            if(handler.get()->check(lexer, token)) {
                return handler.get();
            }
        }
        return nullptr;
    }
private:

    std::vector<std::unique_ptr<Handler>> mHandlers;
};

#endif // HANDLER_PICKER_H
