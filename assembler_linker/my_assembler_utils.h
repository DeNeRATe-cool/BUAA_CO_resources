/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_assembler_utils.h
 * Assembler Functions Description
 *****************************************************************/

#ifndef MY_ASSEMBLER_UTILS_H
#define MY_ASSEMBLER_UTILS_H

#include "lib/tables.h"

/*
 * Function: read_data_segment
 *
 * Description:
 *  This function reads symbols in `.data` segment from INPUT and add them to the SYMTBL.
 *  Note that in order to distinguish in the symbol table whether a symbol
 *  comes from the `.data` segment or the `.text` segment, we append a `%` before the
 *  symbol name when adding the .data segment symbol. Since only underscores and
 *  letters will appear in legal symbols, distinguishing them by adding `%` will
 *  not cause a conflict between the new symbol and the symbols in the assembly file.
 *  Note that the `.data` segment ends with a blank line.
 *
 * Parameters:
 *  input: the input file.
 *  symtbl: the symbol table.
 *
 * Returns: int
 *  the number of bytes in the .data segment.
 *
 * Hint:
 *  Read pass_one() in assembler.c first.
 *  The function you may use: strtok(), skip_comment(), is_valid_label(), add_to_table()
 */
int read_data_segment(FILE *input, SymbolTable *symtbl);

/*
 * Function: write_li
 *
 * Description:
 *  Expand the pseudoinstruction `li` to general instructions, and
 *  write them to the OUTPUT file. This function is called during write_pass_one().
 *
 *  In general cases:
 *  - the number of arguments is 2, the first argument is a register, and the second
 *    argument is an immediate number. They are in args[0] and args[1] respectively.
 *  - the immediate number is in the range of 32-bit signed integer:
 *      - if the immediate number is in the range of 16-bit **signed** integer,
 *        you should use **addiu** to load the immediate number.
 *        (You may use the $zero register.)
 *      - if the immediate number is out of the range of 16-bit but in the range of
 *        32-bit **signed** integer, you should expand it into a lui-ori pair.
 *        (You may use the $at register.)
 *
 * Parameters:
 *  output: the output stream to write to.
 *  name: the name of the instruction.
 *  args: an array of the arguments.
 *  num_args: the number of items in args.
 *
 * Returns: unsigned int
 *  the number of instructions written, 0 if there are any errors.
 *
 * Hint:
 *  - We ignore comma `,` in the instruction and you don't need to output it.
 *  - Use fprintf() to write to OUTPUT. If writing multiple instructions, make sure that
 *  each instruction is on a different line.
 */
unsigned write_li(FILE *output, const char *name, char **args, int num_args);

/*
 * Function: write_rtype
 *
 * Description:
 *  Write all R-type instructions in hexadecimal format to OUTPUT file, except `jr`,
 *  or shift instructions like `sll`. This function is called during translate_inst().
 *
 *  In general cases:
 *  - the number of arguments is 3, and they are all registers in string format.
 *    They are in args[0], args[1] and args[2] respectively.
 *
 * Parameter:
 *  funct: the funct part of instruction.
 *  output: the output stream to write to.
 *  args: an array of the arguments.
 *  num_args: the number of items in args.
 *
 * Returns: int
 *  0 on success and -1 on error.
 *
 * Hint:
 *  You should use translate_reg() to parse registers
 *  and write_inst_hex() to write to OUTPUT. Both are defined in translate_utils.h.
 */
int write_rtype(uint8_t funct, FILE *output, char **args, size_t num_args);

#endif