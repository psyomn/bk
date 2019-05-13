#include "bk/state_machine.h"

#include <map>

namespace bk {
StateMachine StateMachine::defaults() {
  auto ret = StateMachine();

  return ret;
}
}
