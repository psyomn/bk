/*
   Copyright 2019 Simon (psyomn) Symeonidis

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */
#include "bk/token.h"

#include <cstdlib>

namespace bk {
Token::Token(const std::string& tok, std::size_t line) :
  mType(Type::unknown), mToken(tok), mLineNumber(line) {}

Token::~Token() {}

std::ostream& operator<<(std::ostream& stream, const bk::Token& tok) {
  switch (tok.type()) {
  case Token::Type::unknown:
    stream << "unknown(";
    break;

  case Token::Type::id:
    stream << "id(";
    break;

  case Token::Type::word:
    stream << "word(";
    break;

  case Token::Type::symbol:
    stream << "symb(";
    break;

  case Token::Type::punct:
    stream << "punct(";
    break;

  case Token::Type::newline:
    stream << "newline(";
    break;

  default:
    abort();
  }

  return stream << tok.mToken << ":" << tok.mLineNumber << ")";
}
} // namespace bk
