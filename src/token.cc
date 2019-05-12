#include "bk/token.h"

#include <cstdlib>

namespace bk {

Token::Token(const std::string& tok, std::size_t line) :
    mType(Type::unknown), mToken(tok), mLineNumber(line) {}

Token::~Token() {}

std::ostream& operator<<(std::ostream& stream, const bk::Token& tok) {
    switch(tok.type()) {
    case Token::Type::unknown:
        stream << "unknown(";
        break;
    case Token::Type::id:
        stream << "id(";
        break;
    case Token::Type::word:
        stream << "word(";
        break;
    default:
        abort();
    }

    return stream << tok.mToken << ")";
}

} // namespace bk
