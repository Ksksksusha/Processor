#include "disasm.h"

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

    fclose(input_file);
    return buf;
}


void disasm_()
{
    FILE *program = NULL;
    program = fopen("text.txt", "w");

    unsigned char* buf = read_buf("bytecode.bin");

    if (buf == NULL)
    {
        printf("Ошибка открытия buf, переданного в SPU\n \n");
        return;
    }

    unsigned char* ip = buf;

    char* str;

    int cmd = NONE_CMD;

    int reg_n = 5;

    bool read = true;

    Arg_t number;

    while(read)
    {
        //fscanf(bytecode, "%d", &cmd);

        cmd = *ip;
        ip = ip + 1;

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
            //fscanf(bytecode, "%lg", &number);

            number = *((Arg_t*) ip);

            ip = (unsigned char*) (((Arg_t*) ip) + 1);

            fputs(cmd_name[PUSH].name_cmd, program);

            fprintf(program, " %lg\n", number);

            break;

        case RPUSH:

            //fscanf(bytecode, "%d", &reg_n);

            reg_n = *ip;
            ip = ip + 1;

            fputs(cmd_name[11].name_cmd, program);

            //проверить номер регистра

            fprintf(program, " r%cx\n", 'a'+ reg_n);

            break;

        case RPOP:

            //fscanf(bytecode, "%d", &reg_n);

            reg_n = *ip;
            ip = ip + 1;

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

    free(buf);
    fclose(program);
}