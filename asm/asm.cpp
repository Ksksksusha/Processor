#include "asm.h"

#include "../commands.h"

static unsigned char* read_buf(const char* filename)
{
    FILE *input_file = NULL;
    input_file = fopen(filename, "rb");
    
    if (input_file == NULL)
    {
        printf("Ошибка открытия файла, переданного в SPU\n \n");
        return NULL;
    }

    size_t file_size = 0, read_size = 0;

    struct stat filestat;
    stat(filename, &filestat);
    file_size = (size_t)filestat.st_size;

    unsigned char *buf = (unsigned char*)calloc(file_size + 2, sizeof(char));
    read_size = fread(buf, sizeof(char), file_size, input_file);
    if(read_size < file_size){
        printf("fread read less than size!\n");
    }

    buf[read_size] = NON_EXIST_CMD;
    //stop read in spu and disasm

    fclose(input_file);
    return buf;
}

// TODO: return value
void asm_()
{
    FILE *program = NULL;
    program = fopen("program.txt", "r");

    if(program == NULL)
    { 
        printf("File reading error program.txt in ASM\n");
        return;
    }
    
    // TODO: low priority: resize buf
    unsigned char* buf = (unsigned char*)calloc(10000, sizeof(char));

    if(buf == NULL)
    {
        printf("buf pointer is NULL\n");
        // TODO: close program
        return;
    }

    unsigned char* ip = buf;

    int n_cmd = 0;
    int n_arg = 0;
    int n_reg = 0; 


    unsigned char cmd = NONE_CMD; 
    bool read = true;

    Arg_t number = NAN;

    while(read)
    {

        char str[30] = "";

        char str_reg[30] = "";

        if(fscanf(program, "%s", str) != 1)
        {
            break;
        }

        cmd = NONE_CMD;

        // TODO: compare_with_cmds / is_cmd
        for(int i = 0; i < CMD_N; i++)
        {
            if(strcmp(cmd_name[i].name_cmd, str) == 0)
            {
                cmd = cmd_name[i].value;
            }
        }

        // TODO: asm_single_cmd
        switch (cmd)
        {
        case NONE_CMD:
            printf("File reading error.\nCheck the input file and restart the program.\n");
            return;

        case HTL:
            //fprintf(bytecode, "%d\n", cmd); 

            *ip = cmd;                                                                                                     
            ip = ip + 1;   
                                                                                                    
            n_cmd++; 

            printf("File translation is completed.\n");
            read = false;

            break;

        case PUSH:  

            fscanf(program, "%lg\n", &number);
            //fprintf(bytecode, "%d\n%lg\n", cmd, number);

            *ip++ = cmd;
                                                                                                            
            *((Arg_t*) ip) = number;                                                                                                           
            ip = (unsigned char*) (((Arg_t*) ip) + 1);         

            n_cmd++;                                                                                                                       
            n_arg++; 

            break;

        
        case RPUSH: 

            fscanf(program, "%s", str_reg);

            if(strlen(str_reg) == 3 && str_reg[0] == 'r' && (str_reg[1] - 'a') >=0 && (str_reg[1] - 'a') < 4 && str_reg[2] == 'x')
            {
                //fprintf(bytecode, "%d\n%d\n", cmd, (str_reg[1] - 'a'));

                *ip = cmd;                                                                                                     
                ip = ip + 1; 
                                                                                                               
                *ip = (str_reg[1] - 'a');                                                                                                           
                ip = ip + 1;         

                n_cmd++;                                                                                                                       
                n_reg++; 

            }else
            {
                printf("Unknown register. \nCheck the input file and restart the program.\n");
            
                read = false;
            }

            break;


        case RPOP:

            fscanf(program, "%s", str_reg);

            if(strlen(str_reg) == 3 && str_reg[0] == 'r' && (str_reg[1] - 'a') >=0 && (str_reg[1] - 'a') < 4 && str_reg[2] == 'x')
            {
                //fprintf(bytecode, "%d\n%d\n", cmd, (str_reg[1] - 'a'));

                *ip = cmd;                                                                                                     
                ip = ip + 1;
                                                                                                               
                *ip = (str_reg[1] - 'a');                                                                                                           
                ip = ip + 1;         
                                                                                                      
                n_cmd++;                                                                                                                       
                n_reg++; 

            }else
            {
                printf("Unknown register. \nCheck the input file and restart the program.\n");
            
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
        
        //fprintf(bytecode, "%d\n", cmd);

        *ip = cmd;                                                                                                     
        ip = ip + 1;   

        n_cmd++;   

        break;

        default: 
            printf("Unknown command. \nCheck the input file and restart the program.\n");
            
            read = false;
        }
    }


    FILE *bytecode = NULL;
    bytecode = fopen("bytecode.bin", "wb");

    if(bytecode == NULL)
    { 
        printf("File reading error bytecode.bin in ASM\n");
        return;
    }

    fwrite(buf, sizeof(unsigned char), (size_t) (n_cmd + n_arg*8 + n_reg), bytecode);

    free(buf);

    fclose(program);
    fclose(bytecode);
}