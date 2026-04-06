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

// disassemble "load constant" instruction
static int constantInstr(const char* name, Chunk* chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant); // print opcode name, idx of constant
  printValue(chunk->constants.values[constant]); // also print constant itself
  printf("'\n");
  return offset + 2; // 1 for opcode + 1 for operand
}

// disassemble *simple* instruction (e.g. does not take any arguments)
static int simpleInstr(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

int disassembleInstr(Chunk *chunk, int offset) {
  printf("%04d ", offset); // format integer, width 4 (pad with 0s)
  // if this instruction is on the same line as the previous one...
  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]){
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines[offset]); // format int, width 4 (pad with space)
  }

  uint8_t instr = chunk->code[offset];
  switch (instr) {
    case OP_CONSTANT:
      return constantInstr("OP_CONSTANT", chunk, offset);
    case OP_ADD:
      return simpleInstr("OP_ADD", offset);
    case OP_SUBTRACT:
      return simpleInstr("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
      return simpleInstr("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return simpleInstr("OP_DIVIDE", offset);
    case OP_NEGATE:
      return simpleInstr("OP_NEGATE", offset);
    case OP_RETURN:
      return simpleInstr("OP_RETURN", offset);
    default:
      printf("unknown opcode %d\n", instr);
      return offset + 1;
  }
}
