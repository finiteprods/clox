#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  // bytecode for expr -((1.2 + 3.4) / 5.6)
  int constIx = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123); // write opcode
  writeChunk(&chunk, constIx, 123);     // then write its operand

  constIx = addConstant(&chunk, 3.4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constIx, 123);
  writeChunk(&chunk, OP_ADD, 123);

  constIx = addConstant(&chunk, 5.6);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constIx, 123);

  writeChunk(&chunk, OP_DIVIDE, 123);
  writeChunk(&chunk, OP_NEGATE, 123);

  writeChunk(&chunk, OP_RETURN, 123);
  disassembleChunk(&chunk, "test chunk");
  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}
