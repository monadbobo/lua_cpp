#include <functional>
#include <cstdio>

namespace lua {

class FILEStream {

public:
    FILEStream(FILE *f):f_{f}, extraline_{0} { memset(buff_, 0, 1024);}
    const char * getContent(size_t *size);
private:
    int extraline_;
    char buff_[1024];
    FILE *f_;
};

class BuffStream {
public:
    BuffStream(const char *data, size_t size_):s_{data},size_{size_}  {}
    const char * getContent(size_t *size);
private:
    const char *s_;
    size_t size_;
};
 
template <class T> class Stream {
public:
    Stream(T &s) : p_{}, n_ {0}, s_{s} {
    }

    int next() {
        if (n_-- <= 0) {
            p_ = s_.getContent(&n_);

            if (p_ == NULL || n_ == 0) {
                return -1;
            }
        }

        return static_cast<unsigned char> (*p_++);
    }

private:
    const char  *p_;
    size_t n_;
    T s_;
};

}
