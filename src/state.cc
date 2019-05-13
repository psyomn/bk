#include "bk/state.h"

namespace bk {
State::State(Token tok, bool terminal) :
  mToken(tok),
  mTerminal(terminal) {}

State::~State() {}
}
