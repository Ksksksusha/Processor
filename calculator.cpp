#include <asm.h>

#include <disasm.h>

#include <spu.h>

void calculator()
{
    printf("Hi! \nWe have already started making calculations, follow the instructions below\n");

    asm_();

    printf("We have assembled the file.\n");

    printf("Answer: %d\n", calc());

}