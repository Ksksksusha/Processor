#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <malloc.h>
#include <string.h>

void asm_();

void  print_main_info(FILE* bitecode);

void* byte_alignment_8(void* ip);

#endif //ASM_H
