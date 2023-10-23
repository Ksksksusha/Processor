#include "disasm.h"

#include "../commands.h"

#define DEF_CMD(name, num, code)                                                                                                            \
    case DEF_##name                                                                                                                         \
        fputs(#name, program);                                                                                                              \
        fprintf(program, "\n");                                                                                                             \
        if((num &= BYTE_ARG) > 0/*считать arg*/))                                                                                           \
        {                                                                                                                                   \
            arg = *((Arg_t*) ip);                                                                                                           \
            ip = (void*) (((Arg_t*) ip) + 1);                                                                                               \
            fprintf(program, "%lg\n", arg);                                                                                                 \
        }else                                                                                                                               \
        {                                                                                                                                   \
            if((num &= BYTE_REG) > 0/*считать reg_n*/)                                                                                      \
            {                                                                                                                               \
                reg_n = *((int*) ip);                                                                                                       \
                ip = (void*) (((int*) ip) + 1);                                                                                             \                
                fprintf(program, " r%cx\n", 'a'+ reg_n);                                                                                    \                                                                                                                       \
            }                                                                                                                               \
        }                                                                                                                                   \
    


void disasm_()
{
    FILE *program = NULL;
    program = fopen("text.txt", "w");

    FILE *bytecode = NULL;
    bytecode = fopen("bytecode.txt", "r");


    // определяем размер файла
    fseek(bytecode , 0 , SEEK_END);                          // устанавливаем позицию в конец файла
    size_t code_size = (size_t) ftell(bytecode);                            // получаем размер в байтах
    rewind (bytecode);                                       // устанавливаем указатель в конец файла
    
    void* buf = calloc(sizeof(char), (code_size + 1));      // выделить память для хранения содержимого файла
    if (buf == NULL)
    {
        printf("Ошибка выделения памяти для spu.code\n");///ошибка с code
    }
    
    size_t result = fread(buf, 1, code_size, bytecode);       // считываем файл в буфер
    if (result != code_size)
    {
        printf("Ошибка чтения\n");
    }
    
    //содержимое файла теперь находится в буфере


    void* ip = buf;

    char* str;

    int cmd = NONE_CMD;

    int reg_n = 5;

    bool read = true;

    Arg_t number;

    while(read)
    {
        //fscanf(bytecode, "%d", &cmd);

        cmd = *((char*) ip);
        ip = (void*) (((char*) ip) + 1); 

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

#undef DEF_CMD