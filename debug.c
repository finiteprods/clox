#include <stdint.h>
#include <stdio.h>

#include "debug.h"
#include "chunk.h"

void disassembleChunk(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstr(chunk, offset);
  }
}

static int simpleInstr(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

int disassembleInstr(Chunk *chunk, int offset) {
  printf("%04d ", offset);

  uint8_t instr = chunk->code[offset];
  switch (instr) {
    case OP_RETURN:
      return simpleInstr("OP_RETURN", offset);
    default:
      printf("unknown opcode %d\n", instr);
      return offset + 1;
  }
}
