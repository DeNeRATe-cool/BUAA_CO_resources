/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * translate_utils.h
 *****************************************************************/

#ifndef TRANSLATE_UTILS_H
#define TRANSLATE_UTILS_H

#include <stdio.h>
#include <stdint.h>

/*
 * Function: write_inst_string
 *
 * Description:
 *  Writes an instruction in string format to the output file.
 *
 * Parameters:
 *  output: the output file to write to.
 *  name: the name of the instruction.
 *  args: an array of arguments for the instruction.
 *  num_args: the number of arguments.
 *
 * Returns: void
 */
void write_inst_string(FILE *output, const char *name, char **args, int num_args);

/*
 * Function: write_inst_hex
 *
 * Description:
 *  Writes an instruction in hexadecimal format to the output file.
 *
 * Parameters:
 *  output: the output file to write to.
 *  instruction: the instruction in hexadecimal format.
 *
 * Returns: void
 */
void write_inst_hex(FILE *output, uint32_t instruction);

/*
 * Function: is_valid_label
 *
 * Description:
 *  Returns 1 if the input string is a valid label name according to the rules below. Returns 0 otherwise.
 *  Rules:
 *      - Must start with a letter or underscore.
 *      - Subsequent characters can be letters, numbers, or underscores.
 *
 * Parameters:
 *  str: the string to be checked.
 *
 * Returns: int
 *  1 if the input string is a valid label name, 0 otherwise.
 */
int is_valid_label(const char *str);

/*
 * Function: translate_num
 *
 * Description:
 *  Translate the input string into a signed number. The number is then
 *  checked to be within the correct range (note bounds are INCLUSIVE)
 *  ie. NUM is valid if LOWER_BOUND <= NUM <= UPPER_BOUND.
 *  And store the result into the location that OUTPUT points to.
 *
 *  The input may be in either positive or negative, and be in either
 *  decimal or hexadecimal format. It is also possible that the input is not
 *  a valid number.
 *
 * Parameters:
 *  output: the location to store the result.
 *  str: the string to translate into a number.
 *  lower_bound: the lower bound of the range (inclusive) that the number
 *    must be in for it to be considered valid.
 *  upper_bound: the upper bound of the range (inclusive) that the number
 *   must be in for it to be considered valid.
 *
 * Returns: int
 *  0 if the conversion proceeded without errors, or -1 if an error occurred.
 */
int translate_num(long int *output, const char *str, long int lower_bound,
                  long int upper_bound);

/*
 * Function: translate_reg
 *
 * Description:
 *  Translates the register name to the corresponding register number.
 *
 * Parameters:
 *  str: the name of the register.
 *
 * Returns: int
 *  the register number of STR or -1 if the register name is invalid.
 */
int translate_reg(const char *str);

#endif
