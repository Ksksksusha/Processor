#include "asm.h"

#include "disasm.h"

#include "spu.h"

int main()
{
    printf("Hi! \nWe have already started making calculations, follow the instructions below\n");

    asm_();

    printf("We have assembled the file.\n");

    calc();

    printf("We have calculated result.\n");

    disasm_();

    return 0;
}