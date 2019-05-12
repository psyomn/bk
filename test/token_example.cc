#include "bk/token.h"

#include <cassert>

int main(void) {
    bk::Token token("hello", 1);
    assert(token.type() == bk::Token::unknown);
    assert(token.line() == 1);
    return 0;
}
