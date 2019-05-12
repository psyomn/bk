#pragma once

#include "bk/token.h"

#include <string>
#include <cstdint>
#include <ostream>

namespace bk {
struct Token {
    Token(const std::string&, std::size_t);
    ~Token();

    enum Type {unknown, id, word};

    inline Type type() const { return mType; }
    inline std::size_t line() const { return mLineNumber; }

private:
    Type mType;
    std::string mToken;
    std::size_t mLineNumber;

    friend std::ostream& operator<<(std::ostream&, const bk::Token&);
};


} // namespace bk
