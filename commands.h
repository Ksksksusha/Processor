#ifndef COMMANDS_H
#define COMMANDS_H

#include "safety_stack.h"

static const char* SIGN = "shk";

static const int VERSION = 3;

static const int CMD_N = 13;

#define NONE_CMD 0xC0DE

enum commands 
{
    HTL = -1,
    PUSH = 1,
    DIV = 2,
    SUB = 3,
    OUT = 4,
    ADD = 5,
    MUL = 6,
    SQRT = 7,
    SIN = 8,
    COS = 9,
    IN = 10,
    RPOP = 43,
    RPUSH = 33
};

struct spu_struct
{
    safety_stack stk;

    Elem_t reg[4];

    int n_cmd;

    Elem_t* code;
};


typedef struct 
{
    const char* name_cmd;
    int value;
} name;

const name cmd_name[] = {
    {"htl", -1},
    {"push", 1}, // TODO: values from enum
    {"div", 2},
    {"sub", 3},
    {"out", 4},
    {"add", 5},
    {"mul", 6},
    {"sqrt", 7},
    {"sin", 8},
    {"cos", 9},
    {"in", 10},
    {"rpush", 33},
    {"rpop", 43}
};


enum spu_status{NULL_POINTER_STRUCT_SPU = 1 << 13};

void spu_dump(spu_struct* spu);

int spu_ok(spu_struct* spu);

void print_spu_status(spu_struct* spu);

int spu_ctor(spu_struct* spu);

void spu_dtor(spu_struct* spu);

#endif //COMMANDS_H