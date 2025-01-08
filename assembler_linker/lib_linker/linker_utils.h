/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * linker_utils.h
 *****************************************************************/

#ifndef LINKER_UTILS_H
#define LINKER_UTILS_H

#include "../lib/tables.h"

#define LINKER_BUF_SIZE 1024
#define LINKER_IGNORE_CHARS " \n\r\t\v\f"

typedef struct
{
    SymbolTable *table;
    int text_size;
    int data_size;
} RelocData;

/*
 * Function: relocate_inst
 *
 * Description:
 *  Given an instruction that needs relocation, relocate the instruction based on
 *  the given symbol and relocation table.
 *  Note that we need to handle the relocation symbols for the .data segment and
 *  the relocation symbols for the .text segment separately.
 *  For the .text segment, the symbols will only appear in the jump instruction
 *  For .data, it will only appear in the lui and ori instructions,
 *  and we have processed it in the assembler as label@Hi/Low.
 *  You should return error if:
 *      (1) the addr is not in the relocation table.
 *      (2) the symbol name is not in the symbol table.
 *  Otherwise, assume that the relocation will perform successfully.
 *
 * Parameters:
 *  inst: an instruction that needs relocate.
 *  offset: the byte offset of the instruction in the current file.
 *  symtbl: the symbol table.
 *  reltbl: the relocation table.
 *
 * Returns:
 *  the relocated instruction, -1 if error.
 */
int32_t relocate_inst(uint32_t inst, uint32_t offset, SymbolTable *symtbl, SymbolTable *reltbl);

/*
 * Function: calc_data_size
 *
 * Description:
 *  Calculates the number of bytes occupied by the .data of the current file.
 *  Note that after the assembler has processed it, we have already calculated
 *  the number of bytes in the .data segment. It is saved at the beginning of
 *  the .out file as ".data \n bytes".
 *
 * Parameters:
 *  input: file pointer, must be pointing to the beginning of the .data section.
 *
 * Returns:
 *  The number of bytes occupied by the .data of the file INPUT.
 */
int calc_data_size(FILE *input);

/*
 * Function: calc_text_size
 *
 * Description:
 *  Compute number of bytes that the text section takes up. This fuction assumes
 *  that when called, the file pointer is currently at the beginning of the text
 *  section. It also assumes that there will be one instruction per line, and
 *  that the .text section ends with a blank line.
 *
 * Parameters:
 *  input: file pointer, must be pointing to the beginning of the text section.
 *
 * Returns:
 *  The size of the text section in bytes.
 */
int calc_text_size(FILE *input);

/*
 * Function: fill_data
 *
 * Description:
 *  Builds the symbol table and relocation data for a single file.
 *  Read the .data, .text, .symbol, .relocation segments in that order.
 *  The size of the .data and .text segments are read and saved in the
 *  relocation table of the current file. For the .symbol and .relocation
 *  segments, save the symbols in them in the corresponding locations.
 *
 * Parameters:
 *  input:            file pointer.
 *  symtbl:           symbol table.
 *  reldt:            pointer to a Relocdata struct.
 *  base_text_offset: base text offset.
 *  base_data_offset: base data offset.
 *
 * Returns:
 *  0 if no errors, -1 if error.
 *
 * Hint:
 *  Use calc_text_size(), calc_data_size(), add_to_symbol_table();
 */
int fill_data(FILE *input, SymbolTable *symtbl, RelocData *reldt, uint32_t base_text_offset, uint32_t base_data_offset);

#endif