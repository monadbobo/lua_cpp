#include <cstdio>
#include "llex.h"
#include <iostream>

int main()
{
    lua::BuffStream bs(" 1.2 ", sizeof(" 1.2 ") - 1);
    auto stream = std::make_unique<lua::Stream<lua::BuffStream>> (bs);

    auto lexstate = std::make_unique<lua::LexState> (stream);

    std::cout << lexstate->llex() << std::endl;
}
