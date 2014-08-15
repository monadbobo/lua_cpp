#ifndef _LUA_LLEX_INCLUDE_H_
#define _LUA_LLEX_INCLUDE_H_

#include <string>
#include "stream.h"

namespace lua {

enum class Reserved;

typedef union {
    double r;
    std::string ts;
} SemInfo;  /* semantics information */

typedef struct Token {
    int token;
    SemInfo seminfo;
} Token;

class LexState {
public:
    LexState(std::unique_ptr <Stream<BuffStream>>& s)
        :current_{0}, linenumber_{0}, io_{std::move(s)}, buff_{},t_{nullptr} {}

    Reserved llex();
private:
    int                       current_;
    int                       linenumber_;
    int                       lastline_;
    Token                    *t_;
    std::string               buff_;
    std::unique_ptr <Stream<BuffStream>>  io_;

    void save();
    inline void save_and_next() {
        current_ = io_->next();
        buff_ += (char) current_;
    }

    inline bool check_next (const char *set) {
        if (!strchr(set, current_)) {
            return false;
        }
        save_and_next();
        return true;
    }

    bool curr_is_new_line() {
        return current_ == '\n' || current_ == '\r';
    }

    void read_numeral ();
    int skip_sep ();
    void error(const char *Str);

};

} /* namespace lua */

#endif      /* _LUA_LLEX_INCLUDE_H_ */
