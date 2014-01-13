#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "llex.h"

enum RESERVED {
  tok_eof = -1, tok_and ,tok_break,
  tok_do, tok_else, tok_elseif, tok_end, tok_false, tok_for, tok_function,
  tok_if, tok_in, tok_local, tok_nil, tok_not, tok_or, tok_repeat,
  tok_return, tok_then, tok_true, tok_until, tok_while,
  /* other terminal symbols */
  tok_concat, tok_dots, tok_eq, tok_ge, tok_le, tok_ne, tok_number,
  tok_name, tok_string, tok_eos
};


int Stream::next() {
    if (n_-- <= 0) {
        reader_();
    }

    return static_cast<unsigned char> (*p_++);
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

int LexState::llex() {
    for (;;) {
        switch (current_) {
        case '\n':
        case '\r': {
            linenumber_++;
            continue;
        }
        case '-': {
            save_and_next();
            if (current_ != '-') return '-';
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
                return tok_string;
            }
            else if (sep == -1) return '[';
            else error("invalid long string delimiter");
        }
        case '=': {
            save_and_next();
            if (current_ != '=') return '=';
            else { save_and_next(); return tok_eq; }
        }
        case '<': {
            save_and_next();
            if (current_ != '=') return '<';
            else { save_and_next(); return tok_le; }
        }
        case '>': {
            save_and_next();
            if (current_ != '=') return '>';
            else { save_and_next(); return tok_ge; }
        }
        case '~': {
            save_and_next();
            if (current_ != '=') return '~';
            else { save_and_next(); return tok_ne; }
        }
        case '"':
        case '\'': {
            // read_string(ls, current_, seminfo);
            return tok_string;
        }
        case '.': {
            save_and_next();
            if (check_next(".")) {
                if (check_next("."))
                    return tok_dots;   /* ... */
                else return tok_concat;   /* .. */
            }
            else if (!isdigit(current_)) return '.';
            else {
                read_numeral();
                return tok_number;
            }
        }
        case -1: {
            return tok_eos;
        }
        default: {
            if (isspace(current_)) {
                assert(!curr_is_new_line());
                save_and_next();
                continue;
            }
            else if (isdigit(current_)) {
                read_numeral();
                return tok_number;
            }
            else if (isalpha(current_) || current_ == '_') {
                // need add string

                return tok_name;
            }
            else {
                int c = current_;
                save_and_next();
                return c;  /* single-char tokens (+ - / ...) */
            }
        }
        }
    }
}
