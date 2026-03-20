//> Chunks of Bytecode chunk-c
#include <stdlib.h>

#include "chunk.h"
//> chunk-c-include-memory
#include "memory.h"
//< chunk-c-include-memory
//> Garbage Collection chunk-include-vm
#include "vm.h"
//< Garbage Collection chunk-include-vm

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lineCount = 0;      // Chapter 14 - Challenge Question 1
  chunk->lineCapacity = 0;   // Chapter 14 - Challenge Question 1
//> chunk-null-lines
  chunk->lines = NULL;
//< chunk-null-lines
//> chunk-init-constant-array
  initValueArray(&chunk->constants);
//< chunk-init-constant-array
}
//> free-chunk
void freeChunk(Chunk* chunk) {
  FREE_ARRAY(int, chunk->lines, chunk->lineCapacity);   // Chapter 14 - Challenge Question 1
//> chunk-free-constants
  freeValueArray(&chunk->constants);
//< chunk-free-constants
  initChunk(chunk);
}
//< free-chunk
/* Chunks of Bytecode write-chunk < Chunks of Bytecode write-chunk-with-line
void writeChunk(Chunk* chunk, uint8_t byte) {
*/
//> write-chunk
//> write-chunk-with-line
void writeChunk(Chunk* chunk, uint8_t byte, int line) {
//< write-chunk-with-line
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,
        oldCapacity, chunk->capacity);


  }
  
  
  chunk->code[chunk->count] = byte;
  chunk->count++;
  

  if (chunk->lineCount > 0 &&
      chunk->lines[chunk->lineCount - 1].line == line) {
    return;
  }

  if (chunk->lineCapacity < chunk->lineCount + 1) {
    int oldCapacity = chunk->lineCapacity;
    chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
    chunk->lines = GROW_ARRAY(LineStart, chunk->lines,
                              oldCapacity, chunk->lineCapacity);
  }

  LineStart* lineStart = &chunk->lines[chunk->lineCount++];
  lineStart->offset = chunk->count - 1;
  lineStart->line = line;
}
//< write-chunk
//> add-constant
int addConstant(Chunk* chunk, Value value) {
//> Garbage Collection add-constant-push
  push(value);
//< Garbage Collection add-constant-push
  writeValueArray(&chunk->constants, value);
//> Garbage Collection add-constant-pop
  pop();
//< Garbage Collection add-constant-pop
  return chunk->constants.count - 1;
}
//< add-constant

// Chapter 14 - Challenge Question 1
// Added getLine function
int getLine(Chunk* chunk, int instruction) {
  int start = 0;
  int end = chunk->lineCount - 1;

  // Loop until correct line is found
  for (;;) {
    //Check if instruction is before, at, or after the midpoint
    int mid = (start + end) / 2;
    LineStart* line = &chunk->lines[mid];
    if (instruction < line->offset) {
      end = mid - 1;
    } else if (mid == chunk->lineCount - 1 ||
        instruction < chunk->lines[mid + 1].offset) {
      return line->line;
    } else {
      start = mid + 1;
    }
  }
}