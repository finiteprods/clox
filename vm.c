#include <stdio.h>

#include "vm.h"

// single global VM object (instead of passing pointer around)!
VM vm;

void initVM() {}

void freeVM() {}

/// main decode-execute loop of vm
static InterpretResult run() {
#define READ_BYTE() (*vm.ip++) // macro: read byte at ip (next instr's opcode), advance ip
// read next byte as index into chunk's constant table
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for (;;) {
    uint8_t instr;
    switch (instr = READ_BYTE()) {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        printValue(constant);
        printf("\n");
        break;
      }
      case OP_RETURN: {
        return INTERPRET_OK;
      }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk *chunk) {
  vm.chunk = chunk; // store chunk in vm
  vm.ip = vm.chunk->code; // "instr ptr" tracks where in bytecode
  return run(); // run bytecode
}
