/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_linker_utils.c
 * Linker Submission
 *****************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "lib_linker/linker_utils.h"
#include "my_linker_utils.h"

/*
 * You should implement functions below.
 * Detailed information is in my_assembler_utils.h.
 */

int inst_needs_relocation(SymbolTable *reltbl, uint32_t offset)
{
    return get_symbol_for_addr(reltbl, offset) != NULL;
}

int add_to_symbol_table(FILE *input, SymbolTable *table, uint32_t base_text_offset, uint32_t base_data_offset)
{
    char buf[LINKER_BUF_SIZE];
    while(fgets(buf, LINKER_BUF_SIZE, input) != NULL) {
        char *addStr = strtok(buf, LINKER_IGNORE_CHARS);
        char *name = strtok(NULL, LINKER_IGNORE_CHARS);
        if(addStr == NULL || name == NULL) break; // 读入结束
        int add = atoi(addStr);
        if(name[0] == '%') {
            name++;
            add += base_data_offset;
        } else {
            add += base_text_offset;
        }
        if(add_to_table(table, name, add) == -1) return -1;
    }
    return 0;
}