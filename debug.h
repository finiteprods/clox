#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassembleChunk(Chunk *chunk, const char *name);
// returns offset of beginning of next instruction
int disassembleInstr(Chunk* chunk, int offset);

#endif
