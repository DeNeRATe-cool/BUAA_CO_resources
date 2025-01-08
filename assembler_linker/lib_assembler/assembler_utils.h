/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * assembler_utils.h
 *****************************************************************/

#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#include "../lib/tables.h"

#define MAX_ARGS 3
#define ASSEMBLER_BUF_SIZE 1024
#define ASSEMBLER_IGNORE_CHARS " \f\n\r\t\v,()"

/*
 * Function: raise_label_error
 *
 * Description:
 *  Call this function if a label is invalid. You should not be calling this function yourself.
 *
 * Parameters:
 *  input_line: which line of the input file that the error occurred in. Note
 *  that the first line is line 1 and that empty lines are included in the count.
 *  label: the label that is invalid.
 *
 * Returns: void
 *
 */
void raise_label_error(uint32_t input_line, const char *label);

/*
 * Function: raise_extra_arg_error
 *
 * Description:
 *  Call this function if more than MAX_ARGS arguments are found while parsing
 *  arguments.
 *
 * Parameters:
 *  input_line: which line of the input file that the error occurred in. Note
 *  that the first line is line 1 and that empty lines are included in the count.
 *  extra_arg: the first extra argument encountered.
 *
 * Returns: void
 */
void raise_extra_arg_error(uint32_t input_line, const char *extra_arg);

/*
 * Function: raise_inst_error
 *
 * Description:
 *  You should call this function if write_pass_one() or translate_inst()
 *  returns -1.
 *
 * Parameters:
 *  input_line: which line of the input file that the error occurred in. Note
 *  that the first line is line 1 and that empty lines are included in the count.
 *  name: the name of the instruction.
 *  args: the arguments of the instruction.
 *  num_args: the number of arguments of the instruction.
 *
 * Returns: void
 */
void raise_inst_error(uint32_t input_line, const char *name, char **args, int num_args);

/*
 * Function: skip_comment
 *
 * Description:
 *  Truncates the string at the first occurrence of the '#' character.
 *
 * Parameters:
 *  str: the string to be truncated.
 *
 * Returns: void
 */
void skip_comment(char *str);

/*
 * Function: parse_args
 *
 * Description:
 *  A helpful helper function that parses instruction arguments. It raises an error
 *  if too many arguments have been passed into the instruction.
 *
 * Parameters:
 *  input_line: which line of the input file that the error occurred in. Note
 *  that the first line is line 1 and that empty lines are included in the count.
 *  args: the arguments of the instruction.
 *  num_args: the number of arguments of the instruction.
 *
 * Returns: int
 *  0 if no error occurred, -1 otherwise.
 */
int parse_args(uint32_t input_line, char **args, int *num_args);

/*
 * Function: add_if_label
 *
 * Description:
 *  Reads STR and determines whether it is a label (ends in ':'), and if so,
 *  whether it is a valid label, and then tries to add it to the symbol table,
 *  remerber to replace ':' with '\0'.
 *  Four scenarios can happen:
 *      1. STR is not a label (does not end in ':'). Returns 0.
 *      2. STR ends in ':', but is not a valid label. Returns -1.
 *      3a. STR ends in ':' and is a valid label. Addition to symbol table fails.
 *          Returns -1.
 *      3b. STR ends in ':' and is a valid label. Addition to symbol table succeeds.
 *          Returns 1.
 *
 * Parameters:
 *  input_line: the line number of the label.
 *  str: the string to be checked.
 *  addr: the address of the label in the input file.
 *  symtbl: the symbol table.
 *
 * Returns: int
 *  0 if STR is not a label.
 *  1 if STR is a valid label and is added to the symbol table.
 *  -1 if STR is a label but is not a valid label or cannot be added to the symbol table.
 *
 * Hint:
 *  Use is_valid_label(), add_to_table() and raise_label_error().
 */
int add_if_label(uint32_t input_line, char *str, uint32_t addr, SymbolTable *symtbl);

#endif