/*
 * a Lua Implementation for C++
 *
 * Author: Simon Liu
 * Email: simohayha.bobo@gmail.com
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <tuple>
#include <unordered_map>
#include "token.h"

namespace lua {
    class Dictionary
    {
      public:
        static Dictionary& getInstance();
        std::tuple<TokenType, TokenValue, int> lookup(const std::string& name) const;
        bool haveToken(const std::string& name) const;
      private:
        Dictionary();
        void addToken(std::string name, std::tuple<TokenValue, TokenType, int> tokenMeta);

      private:
        // four token property: token name, token value, token type, precedence.
        std::unordered_map<std::string, std::tuple<TokenValue, TokenType, int>> dictionary_;
    };
}

#endif  /* DICTIONARY_H_ */
