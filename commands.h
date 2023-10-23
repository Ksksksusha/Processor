static const char* SIGN = "shk";

static const int VERSION = 3;

static const int CMD_N = 13;

typedef double Arg_t; 

#define NONE_CMD 0xC0DE

#define DEF_CMD(name, num, code)    \
    DEF_##name = num, 


enum commands 
{
    #include "def_cmd.h"
};

enum byte
{
    BYTE_REG = 1<<6,
    BYTE_ARG = 1<<7
};
