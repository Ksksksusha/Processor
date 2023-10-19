#include "disasm.h"

#include "../commands.h"

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

        case NONE_CMD:
            printf("File reading error.\n");
            
            fprintf(program, "File reading error, this file is invalid\n");

            read = false;

            break;

        case HTL:                                               
            fputs(cmd_name[0].name_cmd, program);/////именно 0!!!!!!!!!!

            printf("File translation is completed.\n");

            read = false;

            break;

        case PUSH:            
            fscanf(bytecode, "%lg", &number);

            fputs(cmd_name[PUSH].name_cmd, program);

            fprintf(program, " %lg\n", number);

            break;

        case RPUSH:

            fscanf(bytecode, "%d", &reg_n);

            fputs(cmd_name[11].name_cmd, program);

            //решается бинарником!!!!!!!!!!
            //проверить номер регистра

            fprintf(program, " r%cx\n", 'a'+ reg_n);

            break;

        case RPOP:

            fscanf(bytecode, "%d", &reg_n);

            fputs(cmd_name[12].name_cmd, program);

            fprintf(program, " r%cx\n", 'a'+ reg_n);

            break;



        case DIV:  [[fallthrough]];
        
        case SUB:  [[fallthrough]];
        
        case OUT:  [[fallthrough]];
        
        case ADD:  [[fallthrough]];
        
        case MUL:  [[fallthrough]];
        
        case SQRT: [[fallthrough]];
        
        case SIN:  [[fallthrough]];
        
        case COS:  [[fallthrough]];
        
        case IN:
            fputs(cmd_name[cmd].name_cmd, program);

            fprintf(program, "\n");

            break;

        default: 

            printf ("Unknown command %d in bytecode\n", cmd);
            fprintf(program, "We found unknown command in bytecode, this file is invalid\n");
            
            read = false;
        };

    
    }

    fclose(bytecode);
    fclose(program);
}