#include "spu.h"


void spu_dump(spu_struct* spu)
{
    puts(SIGN);
    printf("\nSPU version%d.0 with %d commands.\n", VERSION, CMD_N);

    printf("rax\trbx\trcx\trdx\n%lg\t%lg\t%lg\t%lg\n", spu->reg[0], spu->reg[1], spu->reg[2], spu->reg[3]);

    STACK_DUMP_S(&spu->stk);
}

int spu_ok(spu_struct* spu)
{
    int errors = 0;
    
    if(spu == NULL)
    {
        errors |= NULL_POINTER_STRUCT_SPU;
        return errors;
    }
    
    errors |= stack_ok_s(&spu->stk);


    return errors;
}

void print_spu_status(spu_struct* spu)
{
    printf("SPU status:\n");

    if(spu == NULL)
    {
        printf("SPU struct has null pointer\n");
        return;
    }

    print_stack_status_s(stack_ok_s(&spu->stk));

    printf("\n\n");
    
}

int spu_ctor(spu_struct* spu)
{
    STACK_CTOR_S(&spu->stk);

    for(int i=0; i < 4; i++)
    {
        spu->reg[i] = TRASH_ELEM;
    }

    return spu_ok(spu);
}

void spu_dtor(spu_struct* spu)
{
    for(int i=0; i < 4; i++)
    {
        spu->reg[i] = TRASH_ELEM;
    }

    //code -> = 0

    stack_dtor_s(&spu->stk);
}

void calc()
{ 
    FILE *bytecode = NULL;
    bytecode = fopen("bytecode.txt", "r");
    
    if (bytecode == NULL)
    {
        printf("Ошибка открытия файла, переданного в SPU\n \n");
        return;
    }

    spu_struct spu = {};
    spu_ctor(&spu);

/*

    // определяем размер файла
    fseek(bytecode , 0 , SEEK_END);                          // устанавливаем позицию в конец файла
    long code_size = ftell(bytecode);                            // получаем размер в байтах
    rewind (bytecode);                                       // устанавливаем указатель в конец файла
    
    spu.code = (Elem_t*) calloc(sizeof(Elem_t), code_size);      // выделить память для хранения содержимого файла
    if (spu.code == NULL)
    {
        printf("Ошибка выделения памяти для spu.code\n");///ошибка с code
    }
    
    size_t result = fread(spu.code, 1, code_size, bytecode);       // считываем файл в буфер
    if (result != code_size)
    {
        printf("Ошибка чтения\n");
    }
    
    //содержимое файла теперь находится в буфере

*/ 

    int command = TRASH_ELEM;
    int reg_n = TRASH_ELEM;
    Arg_t number = TRASH_ELEM;
    Arg_t elem_a = TRASH_ELEM;
    Arg_t elem_b = TRASH_ELEM;
    bool read = true;

    while(read)
    {
        fscanf(bytecode, "%d", &command);

        switch (command)
        {
        case HTL:                                                
            printf("Calculating is complete.\n");

            read = false;

            break;

        case PUSH:                                               
            fscanf(bytecode, "%lg", &number);
            stack_push_s(&spu.stk, number);

            break;

        case DIV:                                                
            CHECK_SIZE(&spu.stk, 2);
            
            elem_b = stack_pop_s(&spu.stk);
            elem_a = stack_pop_s(&spu.stk);

            if(elem_b == 0)
            {
                printf("ERROR:\nDividing by zero\n");
                read = false;
            }else
            {
                stack_push_s(&spu.stk, elem_a / elem_b); 

                break;
            }

            break;

        case SUB:                                                   
            CHECK_SIZE(&spu.stk, 2);
                                                         
            elem_b = stack_pop_s(&spu.stk);
            elem_a = stack_pop_s(&spu.stk);
            stack_push_s(&spu.stk, elem_a - elem_b); // TODO: check return value

            break;

        case OUT:                                                       
            CHECK_SIZE(&spu.stk, 1);
                                                                                                     
            printf("Answer is %lg\n", stack_pop_s(&spu.stk));

            break;

        case ADD:                                                       
            CHECK_SIZE(&spu.stk, 2);
                                                             
            elem_b = stack_pop_s(&spu.stk);
            elem_a = stack_pop_s(&spu.stk);
            stack_push_s(&spu.stk, elem_a + elem_b);

            break;

        case MUL:                                                     
            CHECK_SIZE(&spu.stk, 2);
                                                              
            elem_b = stack_pop_s(&spu.stk);
            elem_a = stack_pop_s(&spu.stk);
            stack_push_s(&spu.stk, elem_a * elem_b);

            break;

        case SQRT:                                                       
            CHECK_SIZE(&spu.stk, 1);
                                                            
            elem_a = stack_pop_s(&spu.stk);
            stack_push_s(&spu.stk, sqrt(elem_a));

            break;

        case SIN:                                                    
            CHECK_SIZE(&spu.stk, 1);
                                                               
            elem_a = stack_pop_s(&spu.stk);
            stack_push_s(&spu.stk, sin(elem_a));

            break;

        case COS:                                                   
            CHECK_SIZE(&spu.stk, 1);
                                                                 
            elem_a = stack_pop_s(&spu.stk);
            stack_push_s(&spu.stk, cos(elem_a));

            break;

        case IN:                                                  
            printf("Enter the number: ");
            scanf("%lg", &number);
            stack_push_s(&spu.stk, number);

            break;

        case RPUSH: 

            fscanf(bytecode, "%d", &reg_n);
            stack_push_s(&spu.stk, spu.reg[reg_n]);

            break;

        case RPOP:

            fscanf(bytecode, "%d", &reg_n);

            spu.reg[reg_n] = stack_pop_s(&spu.stk);

            break;

        default: 

            printf("Unknown command. \nCheck bytecode file and restart the program.\n");

            read = false;

            break;
        }
    }

    stack_dtor_s(&spu.stk);

    fclose(bytecode);

}