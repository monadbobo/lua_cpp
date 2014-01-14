#include "stream.h"

namespace lua {

const char *FILEStream::getContent(size_t *size)
{
    if (extraline_) {
        *size = 1;
        buff_[0] = '\n';
        return buff_;
    }

    if (feof(f_)) {
        return NULL;
    }

    *size = fread(buff_, 1, sizeof(buff_), f_);

    if (*size > 0) {
        return buff_;
    }

    return NULL;
}

const char *BuffStream::getContent(size_t *size)
{
    if (size_  == 0) {
        return NULL;
    }
    *size = size_;
    return s_;
}    

}
