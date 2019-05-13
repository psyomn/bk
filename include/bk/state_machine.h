#pragma once

#include "bk/token.h"
#include "bk/state.h"

#include <map>

namespace bk {
struct StateMachine {
public:

  StateMachine();
  ~StateMachine();

  static StateMachine defaults();
  void                states(std::map<bk::Token::Type, bk::Token::Type>&);

private:

  std::map<State, State>mStates;
};
}
