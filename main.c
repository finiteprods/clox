#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"

static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");
    // read a line from stdin
    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

// return contents of given file
// (by dynamic alloc, passing ownership to caller)
static char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  // first "seek" to eof so we know how many bytes to alloc
  fseek(file, 0L, SEEK_END);
  size_t filesize = ftell(file);
  rewind(file);

  // alloc the string and actually read the file in proper
  char *buffer = (char *)malloc(filesize + 1); // +1 ...
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  size_t bytesRead = fread(buffer, sizeof(char), filesize, file);
  if (bytesRead < filesize) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }
  buffer[bytesRead] = '\0'; // ... for the null byte

  fclose(file);
  return buffer;
}

// run lox code in given file
static void runFile(const char *path) {
  char *source = readFile(path); // ownership of source passed here...
  InterpretResult result = interpret(source);
  free(source); // ...so it has the job of freeing it

  if (result == INTERPRET_COMPILE_ERROR)
    exit(65);
  if (result == INTERPRET_RUNTIME_ERROR)
    exit(70);
}

// recall 1st arg in `argv` is always name of exe!
int main(int argc, const char* argv[]) {
  initVM();

  if (argc == 1) { // no args
    repl();
  } else if (argc == 2) { // 1 arg: assumed to be a path
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  return 0;
}
