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

    bool read = true;

    int number;

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
            fscanf(bytecode, "%d", &number);

            fputs(cmd_name[PUSH].name_cmd, program);

            fprintf(program, " %d\n", number);

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