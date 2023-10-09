#include <disasm.h>

void disasm_()
{
    FILE *program = NULL;
    program = fopen("text.txt", "w");

    FILE *bitecode = NULL;
    bitecode = fopen("bitecode.txt", "r");

    char* str;

    int cmd = 0xC0DE;

    bool read = true;

    int number;

    while(read)
    {
        fscanf(bitecode, "%d", cmd);

        if(cmd == HTL || (cmd >= cmd_name[1].value && cmd <= cmd_name[CMD_N - 1].value))
        {

            switch (cmd)
            {
            case HTL:                                               
                fputs(cmd_name[0].name_cmd, program);
                printf("File translation is completed.\n");
                read = false;

                [[fallthrough]];
            case PUSH:                                             
                fscanf(bitecode, "%d", &number);

                fputs(cmd_name[PUSH].name_cmd, program);

                fprintf(program, "%d\n", number);

                [[fallthrough]];
            default: 
                fputs(cmd_name[cmd].name_cmd, program);

                fprintf(program, "%\n");

            };

        }else
        {
            printf("Invalid bitecode\n");

            fprintf(program, "Invalid file, don`t use it!\n");

            read = false;
        }
        
        
    }
}