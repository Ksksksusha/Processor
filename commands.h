static const char* SIGN = "shk";

static const int VERSION = 3;

static const int CMD_N = 13;

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
    {"htl", -1},
    {"push", 1}, // TODO: values from enum
    {"div", 2},
    {"sub", 3},
    {"out", 4},
    {"add", 5},
    {"mul", 6},
    {"sqrt", 7},
    {"sin", 8},
    {"cos", 9},
    {"in", 10},
    {"rpush", 33},
    {"rpop", 43}
};