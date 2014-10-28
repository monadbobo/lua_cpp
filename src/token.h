/*
 * a Lua Implementation for C++
 *
 * Author: Simon Liu
 * Email: simohayha.bobo@gmail.com
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

namespace lua {

  enum class TokenType {
    /* read  Lua 5.2 Reference Manual (2.1) */
    NIL,
    NUMBER,
    STRING,
    FUNCTION,
    TABLE,

    IDENTIFIER,
    KEYWORDS,
    OPERATORS,
    DELIMITER,
    END_OF_FILE,
    UNKNOWN
  };

  enum class TokenValue {
    AND,
    BREAK,
    DO,
    ELSE,
    ELSEIF,
    END,
    FALSE,
    FOR,
    FUNCTION,
    GOTO,
    IF,
    IN,
    LOCAL,
    NIL,
    NOT,
    OR,
    REPEAT,
    RETURN,
    THEN,
    TRUE,
    UNTIL,
    WHILE,

    /* Operator */
    LEFT_PAREN,        // (
    RIGHT_PAREN,       // )
    LEFT_SQUARE,       // [
    RIGHT_SQUARE,      // ]
    LEFT_BRACE,        // {
    RIGHT_BRACE,       // }
    PLUS,              // +
    MINUS,             // -
    MULTIPLY,          // *
    DIVIDE,            // /
    COMMA,             // ,
    SEMICOLON,         // ;
    COLON,             // :
    PERIOD,            // .
    CONCAT,            // ..
    UPARROW,           // ^
    LENGTH,            // #
    LESS_OR_EQUAL,     // <=
    LESS_THAN,         // <
    GREATER_OR_EQUAL,  // >=
    GREATER_THAN,      // >
    EQUAL,             // =
    NOT_EQUAL,         // ~=
    PERCENT,         // %

    VARARG,            // ...

    UNRESERVED
  };

  class TokenLocation
  {
    public:
      TokenLocation();
      TokenLocation(const std::string& fileName, int line, int column);

      auto toString() const;
    private:
      std::string fileName_;
      int line_;
      int column_;
  };

  class Token
  {
    public:
      Token();
      Token(TokenType type, TokenValue value, const TokenLocation& location,
            std::string name, int precedence);
      Token(TokenType type, TokenValue value, const TokenLocation& location,
            const std::string& strValue, std::string name);
      Token(TokenType type, TokenValue value, const TokenLocation& location,
            double number, std::string name);

              // get token information
      auto getTokenType() const;
      auto getTokenValue() const;
      const auto& getTokenLocation() const;
      auto getTokenName() const;

      // + - * / and so on.
      auto getPrecedence() const;

      // get constant values of token
      auto getNumberValue() const;
      auto getStringValue() const;

   private:
      TokenType type_;
      TokenValue value_;
      TokenLocation location_;
      int           precedence_;
      std::string   name_;

      double number_;
      std::string  str_value_;

  };

  inline auto Token::getTokenType() const
  {
    return type_;
  }

  inline auto Token::getTokenValue() const
  {
    return value_;
  }

  inline auto Token::getTokenName() const
  {
    return name_;
  }

  inline const auto& Token::getTokenLocation() const
  {
    return location_;
  }

  inline auto Token::getNumberValue() const
  {
    return number_;
  }

  inline auto Token::getStringValue() const
  {
    return str_value_;
  }

  inline auto Token::getPrecedence() const
  {
    return precedence_;
  }
}

#endif
