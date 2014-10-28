/*
 * a Lua Implementation for C++
 *
 * Author: Simon Liu
 * Email: simohayha.bobo@gmail.com
 */


#include "token.h"

namespace lua {

TokenLocation::TokenLocation(const std::string& fileName, int line, int column)
    : fileName_(fileName), line_(line), column_(column)
{}

TokenLocation::TokenLocation() : fileName_(""), line_(1), column_(0)
{}

auto TokenLocation::toString() const
{
  return fileName_ + ":" + std::to_string(line_) + ":" + std::to_string(column_) + ":";
}

Token::Token() : type_(TokenType::UNKNOWN), value_(TokenValue::UNRESERVED),
                 location_(std::string(""), 0, 0), name_(""), precedence_(-1)
{}

Token::Token(TokenType type, TokenValue value, const TokenLocation& location,
             std::string name, int precedence)
    : type_(type), value_(value), location_(location), name_(name),
      precedence_(precedence)
{}

Token::Token(TokenType type, TokenValue value, const TokenLocation& location,
             const std::string& str_value, std::string name)
    : type_(type), value_(value), location_(location),
      str_value_(str_value), name_(name), precedence_(-1)
{}

Token::Token(TokenType type, TokenValue value, const TokenLocation& location,
             double number, std::string name)
    : type_(type), value_(value), location_(location),
      number_(number), name_(name), precedence_(-1)
{}

}
