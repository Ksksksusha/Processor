#include "asm.h"

#include "disasm.h"

#include "spu.h"

int main()
{
    printf("Hi! \nWe have already started making calculations, follow the instructions below\n");

    asm_();
    
    calc();

    disasm_();

    return 0;
}