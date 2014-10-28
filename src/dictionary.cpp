/*
 * a Lua Implementation for C++
 *
 * Author: Simon Liu
 * Email: simohayha.bobo@gmail.com
 */

#include "dictionary.h"

namespace lua {


Dictionary::Dictionary() {

  /* Operator precedence in Lua follows the table below, from lower to higher priority:
     or
     and
     <     >     <=    >=    ~=    ==
     ..
     +     -
     *     /     %
     not   #     - (unary)
     ^
  */

  // operator
  addToken("=", std::make_tuple(TokenValue::EQUAL, TokenType::OPERATORS, 0));
  addToken("~=", std::make_tuple(TokenValue::NOT_EQUAL, TokenType::OPERATORS, 3));
  addToken(">=", std::make_tuple(TokenValue::GREATER_OR_EQUAL, TokenType::OPERATORS, 3));
  addToken(">", std::make_tuple(TokenValue::GREATER_THAN, TokenType::OPERATORS, 3));
  addToken("<=", std::make_tuple(TokenValue::LESS_OR_EQUAL, TokenType::OPERATORS, 3));
  addToken("<", std::make_tuple(TokenValue::LESS_THAN, TokenType::OPERATORS, 3));
  addToken("..", std::make_tuple(TokenValue::CONCAT, TokenType::OPERATORS, 4));
  addToken("+", std::make_tuple(TokenValue::PLUS, TokenType::OPERATORS, 5));
  addToken("-", std::make_tuple(TokenValue::MINUS, TokenType::OPERATORS, 5));
  addToken("*", std::make_tuple(TokenValue::MULTIPLY, TokenType::OPERATORS, 6));
  addToken("/", std::make_tuple(TokenValue::DIVIDE, TokenType::OPERATORS, 6));
  addToken("%", std::make_tuple(TokenValue::PERCENT, TokenType::OPERATORS, 6));
  addToken("#", std::make_tuple(TokenValue::LENGTH, TokenType::OPERATORS, 7));
  addToken("^", std::make_tuple(TokenValue::UPARROW, TokenType::OPERATORS, 8));

  // delimiter
  addToken("...", std::make_tuple(TokenValue::VARARG, TokenType::DELIMITER, -1));
  addToken(":", std::make_tuple(TokenValue::COLON, TokenType::DELIMITER, -1));
  addToken(",", std::make_tuple(TokenValue::COMMA, TokenType::DELIMITER, -1));
  addToken("..",std::make_tuple(TokenValue::CONCAT, TokenType::DELIMITER, -1));
  addToken("(", std::make_tuple(TokenValue::LEFT_PAREN, TokenType::DELIMITER, -1));
  addToken("[", std::make_tuple(TokenValue::LEFT_SQUARE, TokenType::DELIMITER, -1));
  addToken(".", std::make_tuple(TokenValue::PERIOD, TokenType::DELIMITER, -1));
  addToken(")", std::make_tuple(TokenValue::RIGHT_PAREN, TokenType::DELIMITER, -1));
  addToken("]", std::make_tuple(TokenValue::RIGHT_SQUARE, TokenType::DELIMITER, -1));
  addToken(";", std::make_tuple(TokenValue::SEMICOLON, TokenType::DELIMITER, -1));
  addToken("{", std::make_tuple(TokenValue::LEFT_BRACE, TokenType::DELIMITER, -1));
  addToken("}", std::make_tuple(TokenValue::RIGHT_BRACE, TokenType::DELIMITER, -1));

  // keywords
  addToken("or", std::make_tuple(TokenValue::OR, TokenType::KEYWORDS,  1));
  addToken("and", std::make_tuple(TokenValue::AND, TokenType::KEYWORDS,  2));
  addToken("not", std::make_tuple(TokenValue::NOT, TokenType::KEYWORDS,  7));
  addToken("break", std::make_tuple(TokenValue::BREAK, TokenType::KEYWORDS,  -1));
  addToken("do", std::make_tuple(TokenValue::DO, TokenType::KEYWORDS,  -1));
  addToken("else", std::make_tuple(TokenValue::ELSE, TokenType::KEYWORDS,  -1));
  addToken("elseif", std::make_tuple(TokenValue::ELSEIF, TokenType::KEYWORDS,  -1));
  addToken("end", std::make_tuple(TokenValue::END, TokenType::KEYWORDS,  -1));
  addToken("false", std::make_tuple(TokenValue::FALSE, TokenType::KEYWORDS,  -1));
  addToken("for", std::make_tuple(TokenValue::FOR, TokenType::KEYWORDS,  -1));
  addToken("function", std::make_tuple(TokenValue::FUNCTION, TokenType::KEYWORDS,  -1));
  addToken("goto", std::make_tuple(TokenValue::GOTO, TokenType::KEYWORDS,  -1));
  addToken("if", std::make_tuple(TokenValue::IF, TokenType::KEYWORDS,  -1));
  addToken("in", std::make_tuple(TokenValue::IN, TokenType::KEYWORDS,  -1));
  addToken("local", std::make_tuple(TokenValue::LOCAL, TokenType::KEYWORDS,  -1));
  addToken("nil", std::make_tuple(TokenValue::NIL, TokenType::KEYWORDS,  -1));
  addToken("repeat", std::make_tuple(TokenValue::REPEAT, TokenType::KEYWORDS,  -1));
  addToken("return", std::make_tuple(TokenValue::RETURN, TokenType::KEYWORDS,  -1));
  addToken("then", std::make_tuple(TokenValue::THEN, TokenType::KEYWORDS,  -1));
  addToken("true", std::make_tuple(TokenValue::TRUE, TokenType::KEYWORDS,  -1));
  addToken("until", std::make_tuple(TokenValue::UNTIL, TokenType::KEYWORDS,  -1));
  addToken("while", std::make_tuple(TokenValue::WHILE, TokenType::KEYWORDS,  -1));

}

Dictionary& Dictionary::getInstance() {

  static Dictionary *dictionary = new Dictionary();

  return *dictionary;
}

void Dictionary::addToken(std::string name, std::tuple<TokenValue, TokenType, int> tokenMeta)
{
  dictionary_.insert(std::pair<decltype(name), decltype(tokenMeta)>(name, tokenMeta));
}

bool Dictionary::haveToken(const std::string& name) const
{
  auto iter = dictionary_.find(name);

  if (iter != dictionary_.end()) {
    return true;
  }

  return false;
}

}
