#include <asm.h>

void asm_()
{
    FILE *program = NULL;
    program = fopen("text.txt", "r");

    FILE *bitecode = NULL;
    bitecode = fopen("bitecode.txt", "w");

    char* str;

    int cmd = 0xC0DE;

    bool read = true;

    int number;

    while(read)
    {
        fscanf(program, "%s", str);

        for(int i = 0; i < CMD_N; i++)
        {
            if(strcmp(cmd_name[i].name_cmd, str) == 0)
            {
                cmd = cmd_name[i].value;
            }
        }
        
        switch (cmd)
        {
        case 0xD0DE:                                               
            printf("Unknown command. \nCheck the input file and restart the program.\n");
            fprintf(bitecode, "Invalid file, don`t use it!");
            
            read = false;

            [[fallthrough]];
        case HTL:                                               
            printf("File translation is completed.\n");
            read = false;

            [[fallthrough]];
        case PUSH:                                             
            fscanf(program, "%d\n", &number);
            fprintf(bitecode, "%d %d", cmd, number);

            [[fallthrough]];
        default: 
            fprintf(bitecode, "%d", cmd);
        };
    }
}