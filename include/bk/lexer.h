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

#include <bk/token.h>
#include <bk/module.h>

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

namespace bk {
struct Lexer {
public:

  Lexer(const std::string&);

  void process(); // TODO maybe this should be moved to a util class
  void tokenizeFile(const std::string&);
  void clearModules() {
    mModules.clear();
  }

  inline std::size_t numModules() const {
    return mModules.size();
  }

private:

  std::size_t             mLineNum;
  std::string             mRoot;
  std::vector<std::string>mFiles;
  std::string             mAcceptExtension;
  std::vector<bk::Module> mModules;

  friend std ::ostream& operator<<(std::ostream& stream, const Lexer& lex) {
    for (auto& module : lex.mModules) stream << module << std::endl;
    return stream;
  }
};
} // namespace bk
