#include <string>
#include  <functional>

typedef union {
  double r;
  std::string ts;
} SemInfo;  /* semantics information */

typedef struct Token {
  int token;
  SemInfo seminfo;
} Token;

class Stream {
    typedef std::function<int ()> ReaderCallback;
public:
    Stream() : p_{}, reader_ {}, n_ {0} {}

    void setReaderCallback(const ReaderCallback &cb) {
        reader_ = cb;
    }

    int next();
private:

    const char  *p_;
    size_t n_;
    ReaderCallback reader_;
};

class LexState {
public:
    LexState(std::unique_ptr <Stream>& s)
        :current_{0}, linenumber_{0}, io_{std::move(s)}, buff_{},t_{nullptr} {}

    int llex();

private:
    int                       current_;
    int                       linenumber_;
    int                       lastline_;
    Token                    *t_;
    std::string               buff_;
    std::unique_ptr <Stream>  io_;

    void save();
    inline void save_and_next() {
        this->current_ = this->io_->next();
        buff_ += (char) this->current_;
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
