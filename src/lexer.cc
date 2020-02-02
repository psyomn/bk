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
#include "bk/lexer.h"
#include "bk/token.h"

#include <filesystem>
#include <sstream>
#include <fstream>

namespace bk {
static bool isPunct(char c) {
  return
    c == '{' || c == '}' ||
    c == '.' || c == ',' ||
    c == ';' || c == ':' ||
    c == '\'' || c == '"' ||
    c == '!' || c == '?' ||
    c == '-' ||
    c == '(' || c == ')' ||
    c == '[' || c == ']' ||
    c == '<' || c == '>';
}

static bool isSymbol(char c) {
  return
    c == '@' || c == '#' || c == '$' || c == '^' ||
    c == '&' || c == '*' || c == '|' || c == '\\' ||
    c == '/';
}

static bool isNewline(char c) {
  return c == '\n';
}

static bool isWhitespace(char c) {
  // ignore chars
  return c == ' ' || c == '\t' || c == '\r';
}

Lexer::Lexer(const std::string& path) :
  mLineNum(1),
  mAcceptExtension(".md") {
  mRoot = path;
}

Lexer::~Lexer() {}

void Lexer::process() {
  namespace fs = std::filesystem;

  for (auto& el : fs::recursive_directory_iterator(mRoot))
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
      // punct = {},.;:'"!?-()[]<>
      ss << c;
      bk::Token tok(ss.str(), linecount);
      tok.type(Token::Type::punct);
      tokens.push_back(std::move(tok));

      ss.str(std::string());
      continue;
    }

    if (isSymbol(c)) {
      // symb = @#$%^&*|\/
      ss << c;
      bk::Token tok(ss.str(), linecount);
      tok.type(Token::Type::symbol);
      tokens.push_back(tok);

      ss.str(std::string());
      continue;
    }

    if (isSymbol(file.peek()) || isPunct(file.peek()) ||
        isWhitespace(file.peek()) || isNewline(file.peek())) {
      // words
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

std::ostream& operator<<(std::ostream& stream, const Lexer& lex) {
  for (auto& module : lex.mModules) stream << module << std::endl;

  return stream;
}
} // namespace bk
