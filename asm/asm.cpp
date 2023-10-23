#include "asm.h"

#include "../commands.h"

#define DEF_CMD(name, num, code)                                                                                                            \
    if(strcmp(cmd, #name) == 0)                                                                                                             \
    {                                                                                                                                       \
        if(((char)num &= BYTE_ARG) > 0 && fscanf(program, "%lg", arg))                                                                            \
        {                                                                                                                                   \
            fprintf(bytecode, "%d\n%lg\n", CMD_##name, arg);                                                                                \
        }else                                                                                                                               \
        {                                                                                                                                   \
            if(((char)num &= BYTE_REG) > 0 && fscanf(program, "%s", str_reg))                                                                     \
            {                                                                                                                               \
                if(strlen(str_reg) == 3 && str_reg[0] == 'r' && (str_reg[1] - 'a') >=0 && (str_reg[1] - 'a') < 4 && str_reg[2] == 'x')      \
                {                                                                                                                           \
                    fprintf(bytecode, "%d\n%d\n", num, (str_reg[1] - 'a'));                                                                 \
                }else                                                                                                                       \
                {                                                                                                                           \
                    printf("Unknown register. \nCheck the input file and restart the program.\n");                                          \
                    fprintf(bytecode, "Invalid file, don`t use it!");                                                                       \
                    read = false;                                                                                                           \
                }                                                                                                                           \
            }                                                                                                                               \
            fprintf(bytecode, "%d\n", num);                                                                                                 \
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
    bytecode = fopen("bytecode.txt", "w");

    if(bytecode == NULL)
    { 
        printf("File reading error bytecode.txt in ASM\n");
        return;
    }

    //print_main_info(bytecode);


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

    

    fclose(program);
    fclose(bytecode);
}