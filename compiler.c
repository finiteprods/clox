#include "compiler.h"
#include "scanner.h"
#include <stdio.h>

// e.g. running on "print 1 + 2;" gives
//    1 31 'print'
//    | 21 '1'
//    |  7 '+'
//    | 21 '2'
//    |  8 ';'
//    2 39 ''
void compile(const char *source) {
  initScanner(source);
  int line = -1;
  for (;;) {
    Token tok = scanToken();
    if (tok.line != line) {
      printf("%4d ", tok.line); // print tok.line with width 4 chars
      line = tok.line;
    } else {
      printf("   | ");
    }
    // * lets you pass in tok.length i.e. how much of string at tok.start to print
    printf("%2d '%.*s'\n", tok.type, tok.length, tok.start);

    if (tok.type == TOKEN_EOF) break;
  }
}
