#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "llex.h"


namespace lua {

enum class Reserved {
  tok_eof = -1, tok_and ,tok_break,
  tok_do, tok_else, tok_elseif, tok_end, tok_false, tok_for, tok_function,
  tok_if, tok_in, tok_local, tok_nil, tok_not, tok_or, tok_repeat,
  tok_return, tok_then, tok_true, tok_until, tok_while,
  /* other terminal symbols */
  tok_concat, tok_dots, tok_eq, tok_ge, tok_le, tok_ne, tok_number,
  tok_name, tok_string, tok_eos
};

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


void LexState::error(const char *Str) {
    fprintf(stderr, "Error: %s in line %d\n", Str, this->linenumber_);
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

Reserved LexState::llex() {
    save_and_next();
    for (;;) {
        switch (current_) {
        case '\n':
        case '\r': {
            linenumber_++;
            continue;
        }
        case '-': {
            save_and_next();
            if (current_ != '-') return static_cast<Reserved>('-');
            /* else is a comment */
            save_and_next();
            if (current_ == '[') {
                int sep = skip_sep();
            }
            /* else short comment */
            while (!curr_is_new_line() && current_ != -1)
                save_and_next();
            continue;
        }
        case '[': {
            int sep = skip_sep();
            if (sep >= 0) {
                // read_long_string(ls, seminfo, sep);
                return Reserved::tok_string;
            }
            else if (sep == -1) return static_cast<Reserved>('[');
            else error("invalid long string delimiter");
        }
        case '=': {
            save_and_next();
            if (current_ != '=') return static_cast<Reserved>('=');
            else { save_and_next(); return Reserved::tok_eq; }
        }
        case '<': {
            save_and_next();
            if (current_ != '=') return static_cast<Reserved>('<');
            else { save_and_next(); return Reserved::tok_le; }
        }
        case '>': {
            save_and_next();
            if (current_ != '=') return static_cast<Reserved>('>');
            else { save_and_next(); return Reserved::tok_ge; }
        }
        case '~': {
            save_and_next();
            if (current_ != '=') return static_cast<Reserved>('~');
            else { save_and_next(); return Reserved::tok_ne; }
        }
        case '"':
        case '\'': {
            // read_string(ls, current_, seminfo);
            return Reserved::tok_string;
        }
        case '.': {
            save_and_next();
            if (check_next(".")) {
                if (check_next("."))
                    return Reserved::tok_dots;   /* ... */
                else return Reserved::tok_concat;   /* .. */
            }
            else if (!isdigit(current_)) return static_cast<Reserved>('.');
            else {
                read_numeral();
                return Reserved::tok_number;
            }
        }
        case -1: {
            return Reserved::tok_eos;
        }
        default: {
            if (isspace(current_)) {
                assert(!curr_is_new_line());
                save_and_next();
                continue;
            }
            else if (isdigit(current_)) {
                read_numeral();
                return Reserved::tok_number;
            }
            else if (isalpha(current_) || current_ == '_') {
                // need add string
                return Reserved::tok_name;
            }
            else {
                int c = current_;
                save_and_next();
                return static_cast<Reserved>(c);  /* single-char tokens (+ - / ...) */
            }
        }
        }
    }
}

}
