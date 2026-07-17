#include <string.h>

#include "common.h"
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

// check whether at end of string i.e. current char is null byte
static bool isAtEnd() {
  return *scanner.current == '\0';
}

// make a (bona fide) token
static Token makeToken(TokenType ty) {
  Token tok;
  tok.type = ty;
  tok.start = scanner.start;
  tok.length = (int)(scanner.current - scanner.start);
  tok.line = scanner.line;
  return tok;
}

// make an error token with given error message (string literal in practice)
static Token errorToken(const char *msg) {
  Token tok;
  tok.type = TOKEN_ERROR;
  tok.start = msg;
  tok.length = (int)strlen(msg);
  tok.line = scanner.line;
  return tok;
}

Token scanToken() {
  scanner.start = scanner.current;
  if (isAtEnd())
    return makeToken(TOKEN_EOF);

  // TODO ...

  return errorToken("Unexpected character.");
}
