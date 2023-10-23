#include "disasm.h"

#include "../commands.h"

#define DEF_CMD(name, num, code)                                                                                                            \
    case DEF_##name                                                                                                                         \
        fputs(#name, program);                                                                                                              \
        fprintf(program, "\n");                                                                                                             \
        if((num &= BYTE_ARG) > 0 && fscanf(program, "%lg", arg))                                                                            \
        {                                                                                                                                   \
            fprintf(bytecode, "%lg\n", arg);                                                                                                \
        }else                                                                                                                               \
        {                                                                                                                                   \
            if((num &= BYTE_REG) > 0 && fscanf(program, "%d", reg_n))                                                                       \
            {                                                                                                                               \
                fprintf(program, " r%cx\n", 'a'+ reg_n);                                                                                    \                                                                                                                       \
            }                                                                                                                               \
        }                                                                                                                                   \
    


void disasm_()
{
    FILE *program = NULL;
    program = fopen("text.txt", "w");

    FILE *bytecode = NULL;
    bytecode = fopen("bytecode.txt", "r");

    char* str;

    int cmd = NONE_CMD;

    int reg_n = 5;

    bool read = true;

    Arg_t number;

    while(read)
    {
        fscanf(bytecode, "%d", &cmd);

        switch (cmd)
        {

        #include "def_cmd.h"
        
        default: 

            printf ("Unknown command %d in bytecode\n", cmd);
            fprintf(program, "We found unknown command in bytecode, this file is invalid\n");
            
            read = false;
        };

    
    }

    fclose(bytecode);
    fclose(program);
}