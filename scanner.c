#include "scanner.h"

// scanner state
typedef struct {
  const char *start; // start of current lexeme
  const char *current; // points to current char of lexeme
  int line; // line no. of lexeme for error reporting
} Scanner;

// toplevel var to save passing around everywhere
Scanner scanner;

void initScanner(const char *source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
}
