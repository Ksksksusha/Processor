#include "spu.h"

#include "../commands.h"

void calc()
{ 
    FILE *bytecode = NULL;
    bytecode = fopen("bytecode.txt", "r");
    
    if (bytecode == NULL)
    {
        printf("Ошибка открытия файла, переданного в SPU \n");
        return;
    }

    safety_stack* stk;
    STACK_CTOR_S(stk);

    Elem_t command = TRASH_ELEM;
    Elem_t number = TRASH_ELEM;
    Elem_t elem_a = TRASH_ELEM;
    Elem_t elem_b = TRASH_ELEM;
    bool read = false;


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
            fscanf(bytecode, "%d", &number);
            stack_push_s(stk, number);

            break;

        case DIV:                                                
            CHECK_SIZE(stk, 2);
            
            elem_b = stack_pop_s(stk);
            elem_a = stack_pop_s(stk);

            if(elem_b == 0)
            {
                printf("ERROR:\nDividing by zero\n");
                read = false;
            }else
            {
                stack_push_s(stk, elem_a / elem_b); 

                break;
            }

            break;

        case SUB:                                                   
            CHECK_SIZE(stk, 2);
                                                         
            elem_b = stack_pop_s(stk);
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, elem_a - elem_b); // TODO: check return value

            break;

        case OUT:                                                       
            CHECK_SIZE(stk, 1);
                                                                                                     
            printf("Answer is %d\n", stack_pop_s(stk));

            break;

        case ADD:                                                       
            CHECK_SIZE(stk, 2);
                                                             
            elem_b = stack_pop_s(stk);
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, elem_a + elem_b);

            break;

        case MUL:                                                     
            CHECK_SIZE(stk, 2);
                                                              
            elem_b = stack_pop_s(stk);
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, elem_a * elem_b);

            break;

        case SQRT:                                                       
            CHECK_SIZE(stk, 1);
                                                            
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, (Elem_t) sqrt(elem_a));

            break;

        case SIN:                                                    
            CHECK_SIZE(stk, 1);
                                                               
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, (Elem_t) sin(elem_a));

            break;

        case COS:                                                   
            CHECK_SIZE(stk, 1);
                                                                 
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, (Elem_t) cos(elem_a));

            break;

        case IN:                                                  
            printf("Enter the number: ");
            scanf("%d", &number);
            stack_push_s(stk, number);

            break;

        default: 

            printf("Unknown command. \nCheck bytecode file and restart the program.\n");

            read = false;

            break;
        }
    }

    fclose(bytecode);

}