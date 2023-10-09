#include "spu.h"

Elem_t calc()
{ 
    FILE *bitecode = NULL;
    bitecode = fopen("bitecode.txt", "r");
    
    if (bitecode == NULL)
    {
        printf("Ошибка открытия файла, переданного в SPU \n");
        return 0;
    }

    safety_stack* stk;
    STACK_CTOR_S(stk);

    Elem_t command = TRASH_ELEM;
    Elem_t number = TRASH_ELEM;
    Elem_t elem_a = TRASH_ELEM;
    Elem_t elem_b = TRASH_ELEM;
    bool read = true;


    while(read)
    {
        fscanf(bitecode, "%d", &command);

        switch (command)
        {
        case HTL:                                                //htl
            printf("File reading is complete.\n");
            read = false;

            [[fallthrough]];
        case PUSH:                                               //push
            fscanf(bitecode, "%d", &number);
            stack_push_s(stk, number);

            [[fallthrough]];
        case DIV:                                                 //div /
            elem_b = stack_pop_s(stk);
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, elem_a / elem_b);

            [[fallthrough]];
        case SUB:                                                 //sub -
            elem_b = stack_pop_s(stk);
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, elem_a - elem_b);

            [[fallthrough]];
        case OUT:                                                 //out
            printf("Calculating is complete.\n");
            read = false;

            [[fallthrough]];
        case ADD:                                                 //add +
            elem_b = stack_pop_s(stk);
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, elem_a + elem_b);

            [[fallthrough]];
        case MUL:                                                 //mul *
            elem_b = stack_pop_s(stk);
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, elem_a * elem_b);

            [[fallthrough]];
        case SQRT:                                                //sqrt
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, sqrt(elem_a));

            [[fallthrough]];
        case SIN:                                                 //sin
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, sin(elem_a));

            [[fallthrough]];
        case COS:                                                 //cos
            elem_a = stack_pop_s(stk);
            stack_push_s(stk, cos(elem_a));

            [[fallthrough]];
        case IN:                                                   //in
            printf("Enter the number: ");
            scanf("%d", number);
            stack_push_s(stk, number);
            [[fallthrough]];
        default: 
            break;
        };
    }

    if(stk->size == 1)
    {
        Elem_t answer = stack_pop_s(stk);
        printf("We calculated the answer: %d", answer);
        return answer;
    }else
    {
        printf("ERROR \n Formula is not correct\n");
        STACK_DUMP_S(stk);
        return NAN;
    }

}