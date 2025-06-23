#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);

  int constIx = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123); // write opcode
  writeChunk(&chunk, constIx, 123); // then write its operand

  writeChunk(&chunk, OP_RETURN, 123);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}
