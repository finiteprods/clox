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

static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

// returns current char w/o consuming it
static char peek() {
  return *scanner.current;
}

// returns next char w/o advancing "current" pointer
static char peekNext() {
  if (isAtEnd())
    return '\0';
  return scanner.current[1];
}

// return true and advance scanner if next char matches *expected*
static bool match(char expected) {
  if (isAtEnd())
    return false;
  if (*scanner.current != expected)
    return false;
  scanner.current++;
  return true;
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

// skip past whitespace and comments
static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    case '\n':
      scanner.line++;
      advance();
      break;
    case '/':
      if (peekNext() == '/') {
        // a comment goes until end of the line
        while (peek() != '\n' && !isAtEnd())
          advance();
      } else
        return;
      break;
    default:
      return;
    }
  }
}

Token scanToken() {
  skipWhitespace();
  scanner.start = scanner.current;
  if (isAtEnd())
    return makeToken(TOKEN_EOF);

  char c = advance();

  switch (c) {
  case '(':
    return makeToken(TOKEN_LEFT_PAREN);
  case ')':
    return makeToken(TOKEN_RIGHT_PAREN);
  case '{':
    return makeToken(TOKEN_LEFT_BRACE);
  case '}':
    return makeToken(TOKEN_RIGHT_BRACE);
  case ';':
    return makeToken(TOKEN_SEMICOLON);
  case ',':
    return makeToken(TOKEN_COMMA);
  case '.':
    return makeToken(TOKEN_DOT);
  case '-':
    return makeToken(TOKEN_MINUS);
  case '+':
    return makeToken(TOKEN_PLUS);
  case '/':
    return makeToken(TOKEN_SLASH);
  case '*':
    return makeToken(TOKEN_STAR);
  case '!':
    return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
  case '=':
    return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
  case '<':
    return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
  case '>':
    return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  }

  return errorToken("Unexpected character.");
}
