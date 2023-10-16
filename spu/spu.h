#include "safety_stack.h"

#define CHECK_SIZE(stk, num) if((stk)->size < num)                                             \
{                                                                                       \
    printf("There are not enough elements in the stack to perform the operation\n");    \
                                                                                        \
    read = false;                                                                       \
                                                                                        \
    break;                                                                              \
}                                                                                       

void calc();

void calculator();