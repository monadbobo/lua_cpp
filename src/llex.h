#ifndef _LUA_LLEX_INCLUDE_H_
#define _LUA_LLEX_INCLUDE_H_

#include <string>
#include <fstream>
#include "token.h"

namespace lua {

  class LexState {

 public:
    LexState(const std::string& fileName);

    Token llex();

    enum class State
    {
      NONE,
      END_OF_FILE,
      IDENTIFIER,
      NUMBER,
      STRING,
      OPERATION
     };
 private:
    char            current_;
    int             linenumber_;
    int             colum_nnumber_;
    int             lastline_;
    Token           token_;
    State           state_;
    std::string     buffer_;
    std::string    fileName_;
    std::ifstream   input_;

    void save();

    void save_and_next();

    inline bool check_next (const char *set) {
      if (!strchr(set, current_)) {
        return false;
      }
      save_and_next();
      return true;
    }

    inline bool curr_is_new_line() {
      return current_ == '\n' || current_ == '\r';
    }

    void read_numeral ();
    int skip_sep ();
    void error(const std::string& msg);

    void            filter_comment_space();
    void            handleNONEState();
    void            handleEOFState();
    void            handleIdentifierState();
    void            handleNumberState();
    void            handleStringState();
    void            handleOperationState();
    void  handleComment();

  };

} /* namespace lua */

#endif      /* _LUA_LLEX_INCLUDE_H_ */
