static const char* SIGN = "shk";

static const int VERSION = 3;

static const int CMD_N = 13;

typedef double Arg_t; 

#define NONE_CMD 0xC0DE

enum commands 
{
    HTL = -1,
    PUSH = 1,
    DIV = 2,
    SUB = 3,
    OUT = 4,
    ADD = 5,
    MUL = 6,
    SQRT = 7,
    SIN = 8,
    COS = 9,
    IN = 10,
    RPOP = 43,
    RPUSH = 33
};


typedef struct 
{
    const char* name_cmd;
    int value;
} name;

const name cmd_name[] = {
    {"htl", HTL},
    {"push", PUSH},
    {"div", DIV},
    {"sub", SUB},
    {"out", OUT},
    {"add", ADD},
    {"mul", MUL},
    {"sqrt", SQRT},
    {"sin", SIN},
    {"cos", COS},
    {"in", IN},
    {"rpush", RPUSH},
    {"rpop", RPOP}
};