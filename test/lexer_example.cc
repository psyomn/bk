#include "bk/lexer.h"

#include <cstdint>
#include <cassert>

int main(void) {
    bk::Lexer lex("sample-book");
    lex.process();

    std::size_t count = lex.numModules();
    assert(count == 1);

    return 0;
}
