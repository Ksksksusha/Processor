#include "asm.h"

#include "../commands.h"

 void print_main_info(FILE* bytecode)
 {
    fputs(SIGN, bytecode);
    fprintf(bytecode, "\nVersion: %d\n", VERSION);
    fprintf(bytecode, "Number of program commands: %d\n", CMD_N);
 }

void asm_()
{
    FILE *program = NULL;
    program = fopen("program.txt", "r");

    if(program == NULL)
    { 
        printf("File reading error text.txt in ASM\n");
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


    int cmd = NONE_CMD; 
    bool read = true;

    int number = NAN;

    while(read)
    {

        char str[30] = "";

        char str_reg[30] = "";

        if(fscanf(program, "%s", str) == EOF)
        {
            break;
        }

        cmd = NONE_CMD;

        for(int i = 0; i < CMD_N; i++)
        {
            if(strcmp(cmd_name[i].name_cmd, str) == 0)
            {
                cmd = cmd_name[i].value;
            }
        }

        switch (cmd)
        {
        case NONE_CMD:  

            printf("File reading error.\nCheck the input file and restart the program.\n");
            fprintf(bytecode, "File reading error, this file is invalid\n");

            return;
            
            read = false;

            break;

        case HTL:     

            fprintf(bytecode, "%d\n", cmd);                                          
            printf("File translation is completed.\n");
            read = false;

            break;

        case PUSH:  

            fscanf(program, "%d\n", &number);
            fprintf(bytecode, "%d\n%d\n", cmd, number);

            break;

        
        case RPUSH: 

            fscanf(program, "%s", str_reg);

            if(strlen(str_reg) == 3 && str_reg[0] == 'r' && (str_reg[1] - 'a') >=0 && (str_reg[1] - 'a') < 4 && str_reg[2] == 'x')
            {
                fprintf(bytecode, "%d\n%d\n", cmd, (str_reg[1] - 'a'));
            }else
            {
                printf("Unknown register. \nCheck the input file and restart the program.\n");
                fprintf(bytecode, "Invalid file, don`t use it!");
            
                read = false;
            }

            break;


        case RPOP:

            fscanf(program, "%s", str_reg);

            if(strlen(str_reg) == 3 && str_reg[0] == 'r' && (str_reg[1] - 'a') >=0 && (str_reg[1] - 'a') < 4 && str_reg[2] == 'x')
            {
                fprintf(bytecode, "%d\n%d\n", cmd, (str_reg[1] - 'a'));
            }else
            {
                printf("Unknown register. \nCheck the input file and restart the program.\n");
                fprintf(bytecode, "Invalid file, don`t use it!");
            
                read = false;
            }

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
        
        fprintf(bytecode, "%d\n", cmd);

        break;

        default: 
            printf("Unknown command. \nCheck the input file and restart the program.\n");
            fprintf(bytecode, "Invalid file, don`t use it!");
            
            read = false;
        }
    }

    fclose(program);
    fclose(bytecode);
}