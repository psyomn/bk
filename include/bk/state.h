#pragma once

namespace bk {
struct State {
  State(Token tok,
        bool  terminal);
  ~State();

private:

  Token mToken;
  bool  mTerminal;
};
}
