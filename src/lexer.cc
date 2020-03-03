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

#include "bk/intrinsics.h"

#include "bk/lexer.h"
#include "bk/token.h"

#include <filesystem>
#include <sstream>
#include <fstream>

namespace bk {
static PURE bool isPunct(char c) {
  static const std::string pattern = "{}.,;:\\\"!?-()[]<>";

  return pattern.find_first_of(c) != std::string::npos;
}

static PURE bool isSymbol(char c) {
  static const std::string pattern = "@#$^&*|\\/";

  return pattern.find_first_of(c) != std::string::npos;
}

static PURE bool isNewline(char c) {
  return c == '\n';
}

static PURE bool isWhitespace(char c) {
  // ignore chars
  static const std::string pattern = " \t\r";

  return pattern.find_first_of(c) != std::string::npos;
}

Lexer::Lexer(const std::string& path) :
  mLineNum(1),
  mAcceptExtension(".md") {
  mRoot = path;
}

void Lexer::process() {
  namespace fs = std::filesystem;

  for (const auto& el : fs::recursive_directory_iterator(mRoot))
    if (el.path().extension() == mAcceptExtension) mFiles.push_back(el.path());

  for (const auto& path : mFiles) tokenizeFile(path);
}

void Lexer::tokenizeFile(const std::string& filename) {
  std::ifstream file(filename, std::ifstream::in);
  std::stringstream ss;
  std::vector<bk::Token> tokens;
  std::size_t linecount = 0;
  char c;

  while (file.get(c)) {
    if (isWhitespace(c)) continue;

    if (isNewline(c)) {
      linecount++;
      bk::Token tok("", linecount);
      tok.type(Token::Type::newline);
      tokens.push_back(tok);

      ss.str({});
      continue;
    }

    if (isPunct(c)) {
      ss << c;
      bk::Token tok(std::move(ss.str()), linecount);
      tok.type(Token::Type::punct);
      tokens.push_back(std::move(tok));

      ss.str(std::string());
      continue;
    }

    if (isSymbol(c)) {
      ss << c;
      bk::Token tok(ss.str(), linecount);
      tok.type(Token::Type::symbol);
      tokens.push_back(tok);

      ss.str(std::string());
      continue;
    }

    if (isSymbol(file.peek()) || isPunct(file.peek()) ||
        isWhitespace(file.peek()) || isNewline(file.peek())) {
      if (ss.str() == std::string("")) continue;

      ss << c;

      bk::Token tok(ss.str(), linecount);
      tok.type(Token::Type::word);
      tokens.push_back(tok);

      ss.str(std::string());
      continue;
    }

    ss << c;
  }

  bk::Module mod(filename, tokens);
  mModules.push_back(mod);
}
} // namespace bk
