#include "bk/lexer.h"

int main(int argc, char *argv[]) {
  bk::Lexer lex(".");
  lex.process();
  return 0;
}
