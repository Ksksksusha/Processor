#include "asm.h"

#include "disasm.h"

#include "spu.h"

#include "../commands.h"


int main()
{
    printf("Hi! \nWe have already started making calculations, follow the instructions below\n");

    spu_struct spu = {};
    spu_ctor(&spu);

    spu.code = (Elem_t*) calloc(100, sizeof(Elem_t));

    asm_(&spu);

    calc(&spu);

    disasm_();

    printf("\n---------------------------------------------------------------------------\nCode is:\n");

    for(int i=0; i < spu.n_cmd; i++)
    {
        printf("%d ", *(spu.code + i));
    }

    spu_dtor(&spu);

    return 0;
}