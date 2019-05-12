#include "bk/module.h"

#include <iostream>

namespace bk {
Module::Module(const std::string& filename, std::vector<bk::Token>& tokens) {
  mFilename = filename;
  mTokens   = tokens;
}

std::ostream& operator<<(std::ostream& stream, const Module& module) {
  stream << module.mFilename << " "
         << module.mTokens.size()
         << std::endl << "   ";

  for (auto& token : module.mTokens) stream << token << " ";

  return stream;
}
} //  namespace bk
