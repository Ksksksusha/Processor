#include "asm.h"

#include "../commands.h"

#define DEF_CMD(name, num, code)                                                                                                            \
    if(strcmp(cmd, #name) == 0)                                                                                                             \
    {                                                                                                                                       \
        if((num &= BYTE_REG) > 0 && fscanf(program, "%lg", &arg))                                                                      \
        {                                                                                                                                   \
            /*fprintf(bytecode, "%d\n%lg\n", CMD_##name, arg);*/                                                                            \
            *((char*) ip) = CMD_##name;                                                                                                     \
            ip = (void*) (((char*) ip) + 1);                                                                                                \
            *((Arg_t*) ip) = arg;                                                                                                           \
            ip = (void*) (((Arg_t*) ip) + 1);                                                                                               \
            n_cmd++;                                                                                                                        \
            n_arg++;                                                                                                                        \
        }else                                                                                                                               \
        {                                                                                                                                   \
            if((num &= BYTE_REG) > 0 && fscanf(program, "%s", str_reg))                                                               \
            {                                                                                                                               \
                if(strlen(str_reg) == 3 && str_reg[0] == 'r' && (str_reg[1] - 'a') >=0 && (str_reg[1] - 'a') < 4 && str_reg[2] == 'x')      \
                {                                                                                                                           \
                    /*fprintf(bytecode, "%d\n%d\n", num, (str_reg[1] - 'a'));  */                                                           \
                    *((char*) ip) = CMD_##name;                                                                                             \
                    ip = (void*) (((char*) ip) + 1);                                                                                        \
                    *((int*) ip) = (str_reg[1] - 'a');                                                                                      \
                    ip = (void*) (((int*) ip) + 1);                                                                                         \
                    n_cmd++;                                                                                                                \
                    n_reg++;                                                                                                                \
                }else                                                                                                                       \
                {                                                                                                                           \
                    printf("Unknown register. \nCheck the input file and restart the program.\n");                                          \
                    fprintf(bytecode, "Invalid file, don`t use it!");                                                                       \
                    read = false;                                                                                                           \
                }                                                                                                                           \
            }                                                                                                                               \
            /*fprintf(bytecode, "%d\n", num); */                                                                                            \
            *((char*) ip) = CMD_##name;                                                                                                     \
            ip = (void*) (((char*) ip) + 1);                                                                                                \
            n_cmd++;                                                                                                                        \
        }                                                                                                                                   \
    }else



void asm_()
{
    FILE *program = NULL;
    program = fopen("program.txt", "r");

    if(program == NULL)
    { 
        printf("File reading error program.txt in ASM\n");
        return;
    }

    FILE *bytecode = NULL;
    bytecode = fopen("bytecode.txt", "wb");

    if(bytecode == NULL)
    { 
        printf("File reading error bytecode.txt in ASM\n");
        return;
    }

    void* buf = calloc(1000, sizeof(char));

    void* ip = buf;

    int n_cmd = 0;
    int n_arg = 0;
    int n_reg = 0;

    if(buf == NULL)
    {
        printf("buf pointer is NULL\n");
        return;
    }

    char cmd[30] = "";

    bool read = true;

    while(fscanf(program, "%s", cmd) > 0 && read)
    {

        char str_reg[30] = "";

        Arg_t arg = NAN;


        #include "def_cmd.h"
        /*else*/ 
        {
            printf("Unknown command. \nCheck the input file and restart the program.\n");
            fprintf(bytecode, "Invalid file, don`t use it!");
            
            read = false;
        }


    }

    fwrite(buf, sizeof(char), (size_t) (n_cmd + n_arg*8 + n_reg*4), bytecode);

    fclose(program);
    fclose(bytecode);
}

#undef DEF_CMD