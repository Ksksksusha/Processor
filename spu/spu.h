#include "safety_stack.h"

#define CHECK_SIZE(stk, num) if((stk)->size < num)                                             \
{                                                                                       \
    printf("There are not enough elements in the stack to perform the operation\n");    \
                                                                                        \
    read = false;                                                                       \
                                                                                        \
    break;                                                                              \
}            

enum spu_status{NULL_POINTER_STRUCT_SPU = 1 << 13};

struct spu_struct
{
    safety_stack stk;

    Elem_t reg[4];
};

void spu_dump(spu_struct* spu);

int spu_ok(spu_struct* spu);

void print_spu_status(spu_struct* spu);

int spu_ctor(spu_struct* spu);

void spu_dtor(spu_struct* spu);

void calc();