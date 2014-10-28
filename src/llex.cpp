#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "llex.h"
#include "token.h"

namespace lua {

LexState::LexState(const std::string& fileName)
    :current_{0}, linenumber_{0},  colum_nnumber_{0}, fileName_{fileName}, state_{State::NONE}, token_{}, buffer_{}
{
  input_.open(fileName_);

  if (input_.fail())
  {
    error("When trying to open file " + fileName_ + ", occurred error.");
  }
}

int LexState::skip_sep () {
  int count = 0;
  int s = current_;
  assert(s == '[' || s == ']');
  save_and_next();
  while (this->current_ == '=') {
    save_and_next();
    count++;
  }
  return (current_ == s) ? count : (-count) - 1;
}


void LexState::error(const std::string& msg) {
  std::cerr << msg << " in line:" << this->linenumber_ << ",in colum: " << this->colum_nnumber_ << std::endl;
}

void LexState::read_numeral () {
  assert(isdigit(current_));
  do {
    save_and_next();
  } while (isdigit(current_) || current_ == '.');
  if (check_next("Ee")) {
    /* optional exponent sign */
    check_next("+-");
  }
  while (isalnum(current_) || current_ == '_') {
    save_and_next();
  }
}

void LexState::save_and_next() {
  current_ = input_.get();
}

void LexState::handleComment()
{
  if (current_ == '-' && input_.peek() == '-') {
    save_and_next();
    save_and_next();
    while (!curr_is_new_line() && current_ != std::istream::traits_type::eof())
      save_and_next();
  }
}


void LexState::filter_comment_space()
{
  do
  {
    while (std::isspace(current_))
    {
      save_and_next();
    }

    handleComment();
  } while (std::isspace(current_));
}


void LexState::handleNONEState()
{
    save_and_next();

    if (state_ == State::NONE) {

      filter_comment_space();

      if (std::isalpha(current_))
      {
        state_ = State::IDENTIFIER;
      }
      // if it is digit or xdigit
      else if (std::isdigit(current_))
      {
        state_ = State::NUMBER;
      }

      else if (current_ == '\"')
      {
        state_ = State::STRING;
      }
      else
      {
        state_ = State::OPERATION;
      }
    }
}

Token LexState::llex() {
  save_and_next();

  for (;;) {

    if (current_ == '\n' || current_ == '\r') {
      linenumber_++;
      colum_nnumber_ = 0;
    } else {
      colum_nnumber_++;
    }

    switch (state_) {
      case State::NONE:
        handleNONEState();
        break;

      case State::END_OF_FILE:
        handleEOFState();
        break;

      case State::IDENTIFIER:
        handleIdentifierState();
        break;

      case State::NUMBER:
        handleNumberState();
        break;

      case State::STRING:
        handleStringState();
        break;

      case State::OPERATION:
        handleOperationState();
        break;

      default:
        error("Match token state error.");
        break;
    }
  }

  return token_;
}

}
