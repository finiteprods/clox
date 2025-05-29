#include <stdint.h>
#include <stdio.h>

#include "debug.h"
#include "chunk.h"
#include "value.h"

void disassembleChunk(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstr(chunk, offset);
  }
}

/// disassemble "load constant" instruction
static int constantInstr(const char* name, Chunk* chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant); // print opcode name, idx of constant
  printValue(chunk->constants.values[constant]); // also print constant itself
  printf("'\n");
  return offset + 2; // 1 for opcode + 1 for operand
}

static int simpleInstr(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

/// returns offset of beginning of next instruction
int disassembleInstr(Chunk *chunk, int offset) {
  printf("%04d ", offset);

  uint8_t instr = chunk->code[offset];
  switch (instr) {
    case OP_CONSTANT:
      return constantInstr("OP_CONSTANT", chunk, offset);
    case OP_RETURN:
      return simpleInstr("OP_RETURN", offset);
    default:
      printf("unknown opcode %d\n", instr);
      return offset + 1;
  }
}
