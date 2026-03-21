//> A Virtual Machine vm-h
#ifndef clox_vm_h
#define clox_vm_h

/* A Virtual Machine vm-h < Calls and Functions vm-include-object
#include "chunk.h"
*/
//> Calls and Functions vm-include-object
#include "object.h"
//< Calls and Functions vm-include-object
//> Hash Tables vm-include-table
#include "table.h"
//< Hash Tables vm-include-table
//> vm-include-value
#include "value.h"
//< vm-include-value
//> stack-max

//< stack-max
/* A Virtual Machine stack-max < Calls and Functions frame-max
#define STACK_MAX 256
*/
//> Calls and Functions frame-max
#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)
//< Calls and Functions frame-max
//> Calls and Functions call-frame

typedef struct {
/* Calls and Functions call-frame < Closures call-frame-closure
  ObjFunction* function;
*/
//> Closures call-frame-closure
  ObjClosure* closure;
//< Closures call-frame-closure
  uint8_t* ip;
  Value* slots;
} CallFrame;
//< Calls and Functions call-frame

// Chapter 15 - Challenge Question 3
typedef struct {
  Chunk* chunk;
  uint8_t* ip;

  Value* stack;
  int stackCount;
  int stackCapacity;
} VM;

//> interpret-result
typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

//< interpret-result
//> Strings extern-vm
extern VM vm;

//< Strings extern-vm
void initVM();
void freeVM();
/* A Virtual Machine interpret-h < Scanning on Demand vm-interpret-h
InterpretResult interpret(Chunk* chunk);
*/
//> Scanning on Demand vm-interpret-h
InterpretResult interpret(const char* source);
//< Scanning on Demand vm-interpret-h
//> push-pop
void push(Value value);
Value pop();
//< push-pop

#endif
