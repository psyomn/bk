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
  ~Lexer();

  void process(); // TODO maybe this should be moved to a util class
  void tokenizeFile(const std::string&);
  void clearModules() {
    mModules.clear();
  }

  inline std::size_t numModules() {
    return mModules.size();
  }

private:

  std::size_t             mLineNum;
  std::string             mRoot;
  std::vector<std::string>mFiles;
  std::string             mAcceptExtension;
  std::vector<bk::Module> mModules;

  friend std ::ostream& operator<<(std::ostream&,
                                   const Lexer&);
};
} // namespace bk
