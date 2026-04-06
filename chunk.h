#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN,
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int* lines; // ith entry is line no. for code[i]
  ValueArray constants; // constant pool for the chunk
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
// write `byte` of code (with `line` number in source code) to `chunk`
void writeChunk(Chunk* chunk, uint8_t byte, int line);
// add constant `value` to `chunk`'s constant pool and return its index
int addConstant(Chunk* chunk, Value value);

#endif
