#pragma once

#include "bk/module.h"

#include <vector>

namespace bk {
struct Parser {
public:

  Parser(std::vector<Module>&);
  ~Parser() {}

  void parse();

private:
};
}
