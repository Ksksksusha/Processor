#include "../commands.h"

#define CHECK_SIZE(stk, num) if((stk)->size < num)                                             \
{                                                                                       \
    printf("There are not enough elements in the stack to perform the operation\n");    \
                                                                                        \
    read = false;                                                                       \
                                                                                        \
    break;                                                                              \
}            


void calc(spu_struct* spu);