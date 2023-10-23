//DEF_CMD(name, num, code);

DEF_CMD(htl  , -1,                          \
    printf("Calculating is complete.\n");   \
    read = false;                           \
    )                                       

DEF_CMD(push ,  65,                         \
    fscanf(bytecode, "%lg", &number);       \
    stack_push_s(&spu.stk, number);         \
    )

DEF_CMD(div  ,  2,                              \
    CHECK_SIZE(&spu.stk, 2);                    \           
    elem_b = stack_pop_s(&spu.stk);             \
    elem_a = stack_pop_s(&spu.stk);             \
    if(elem_b == 0)                             \
    {                                           \
        printf("ERROR:\nDividing by zero\n");   \
        read = false;                           \
    }else                                       \
    {                                           \
        stack_push_s(&spu.stk, elem_a / elem_b);\
        break;                                  \
    }                                           \
    )

DEF_CMD(sub  ,  3,                              \
    CHECK_SIZE(&spu.stk, 2);                    \                                                   
    elem_b = stack_pop_s(&spu.stk);             \
    elem_a = stack_pop_s(&spu.stk);             \
    stack_push_s(&spu.stk, elem_a - elem_b);    \ 
    )

// TODO: check return value

DEF_CMD(out  ,  4,                                    \  
    CHECK_SIZE(&spu.stk, 1);                          \                                                                                                 
    printf("Answer is %lg\n", stack_pop_s(&spu.stk)); \
)

DEF_CMD(add  ,  5,                                      
    CHECK_SIZE(&spu.stk, 2);                           \                                                              
    elem_b = stack_pop_s(&spu.stk);                    \
    elem_a = stack_pop_s(&spu.stk);                    \
    stack_push_s(&spu.stk, elem_a + elem_b);           \
)

DEF_CMD(mul  ,  6,                                      \
    CHECK_SIZE(&spu.stk, 2);                            \                                                             
    elem_b = stack_pop_s(&spu.stk);                     \
    elem_a = stack_pop_s(&spu.stk);                     \
    stack_push_s(&spu.stk, elem_a * elem_b);            \
)

DEF_CMD(sqrt ,  7,                                      \
    CHECK_SIZE(&spu.stk, 1);                            \                                                           
    elem_a = stack_pop_s(&spu.stk);                     \
    stack_push_s(&spu.stk, sqrt(elem_a));               \
)

DEF_CMD(sin  ,  8,                                      \
    CHECK_SIZE(&spu.stk, 1);                            \                                                              
    elem_a = stack_pop_s(&spu.stk);                     \
    stack_push_s(&spu.stk, sin(elem_a));                \
)

DEF_CMD(cos  ,  9,                                      \
    CHECK_SIZE(&spu.stk, 1);                            \                                                                
    elem_a = stack_pop_s(&spu.stk);                     \
    stack_push_s(&spu.stk, cos(elem_a));                \
)

DEF_CMD(in   , 10,                                      \
    printf("Enter the number: ");                       \
    scanf("%lg", &number);                              \   
    stack_push_s(&spu.stk, number);                     \
)

//DEF_CMD(jmp  , 12, 0, )

DEF_CMD(rpush, 33,                                      \
    fscanf(bytecode, "%d", &reg_n);                     \
    stack_push_s(&spu.stk, spu.reg[reg_n]);             \
)

DEF_CMD(rpop , 43,                                      \
    fscanf(bytecode, "%d", &reg_n);                     \
    spu.reg[reg_n] = stack_pop_s(&spu.stk);             \
)

//DEF_CMD()