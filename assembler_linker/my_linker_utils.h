/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_linker_utils.h
 * Linker Functions Description
 *****************************************************************/

#ifndef MY_LINKER_UTILS_H
#define MY_LINKER_UTILS_H

#include <stdlib.h>

#include "lib_linker/linker_utils.h"

/*
 * Function: inst_needs_relocation
 *
 * Description:
 *  Detect whether the given instruction needs relocation.
 *
 * Parameters:
 *  reltbl: the relocation table.
 *  offset: the address of an instruction in the file.
 *
 * Returns: int
 *  1 if the instruction needs relocation, 0 otherwise.
 *
 * Hint:
 *  Use get_symbol_for_addr().
 */
int inst_needs_relocation(SymbolTable *reltbl, uint32_t offset);

/*
 * Function: add_to_symbol_table
 *
 * Description:
 *  Add entries from the `.symbol` OR `.relocation` section into the SymbolTable.
 *  The given file pointer is already pointed to the begining of the section.
 *  (the line immediately after `.symbol` or `.relocation`). Each line is already
 *  of the format "<number>\t<string>\n", and the section ends with a blank line.
 *
 *  Similarly, when we add symbols to the symbol table, we need to process the symbols
 *  in the `.data` segment and the `.text` segment separately. The symbols in the `.data`
 *  segment should have an offset based on base_data_offset, and the symbols in the
 *  `.text` segment should have an offset based on base_text_offset. The two are
 *  distinguished by the character `%` that the assembler adds to the beginning of the
 *  `.data` segment symbols' names, and remember that you only need to remove the `%` when
 *  adding symbols in `.data` segment to the symbol table in this function.
 *
 * Parameters:
 *  input: file pointer.
 *  table: the symbol table.
 *  base_text_offset: base text offset.
 *  base_data_offset: base data offset.
 *
 * Returns: int
 *  0 if no errors, -1 if error.
 *
 * Hint:
 *  Use add_to_table().
 */
int add_to_symbol_table(FILE *input, SymbolTable *table, uint32_t base_text_offset, uint32_t base_data_offset);

#endif