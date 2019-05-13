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
#pragma once

#include "bk/token.h"

#include <string>
#include <cstdint>
#include <ostream>

namespace bk {
struct Token {
  enum Type { unknown, id, word, punct, symbol, newline };

  Token(const std::string&,
        std::size_t);
  ~Token();

  inline Type type() const {
    return mType;
  }

  inline void type(Type t) {
    mType = t;
  }

  inline std::size_t line() const {
    return mLineNumber;
  }

private:

  Type        mType;
  std::string mToken;
  std::size_t mLineNumber;

  friend std ::ostream& operator<<(std::ostream&,
                                   const bk::Token&);
};
} // namespace bk
