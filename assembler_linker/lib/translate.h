/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * translate.h
 *****************************************************************/

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "tables.h"

/*
 * Function: write_pass_one
 *
 * Description:
 *  Writes instructions during the assembler's first pass to OUTPUT. The case
 *  for general instructions has already been completed, but you need to write
 *  code to translate the li pseudoinstructions. Your pseudoinstruction
 *  expansions should not have any side effects.
 *
 * Parameters:
 *  output: the output stream to write to.
 *  name: the name of the instruction.
 *  args: an array of the arguments.
 *  num_args: the number of items in args.
 *
 * Returns: unsigned int
 *  the number of instructions written, 0 if there were any errors.
 */
unsigned write_pass_one(FILE *output, const char *name, char **args, int num_args);

/*
 * Function: translate_inst
 *
 * Description:
 *  Writes the instruction in hexadecimal format to OUTPUT during pass #2.
 *  The symbol table (SYMTBL) is given for any symbols that need to be resolved
 *  at this step. If a symbol should be relocated, it should be added to the
 *  relocation table (RELTBL), and the fields for that symbol should be set to
 *  all zeros.
 *
 * Parameters:
 *  output: the output stream to write to.
 *  name: the name of the instruction.
 *  args: an array of the arguments.
 *  num_args: the number of items in args.
 *  symtbl: a pointer to the SymbolTable structure.
 *  reltbl: a pointer to the RelacationSymbolTable structure.
 *
 * Returns: int
 *  0 on success and -1 on error.
 */
int translate_inst(FILE *output, const char *name, char **args, size_t num_args,
                   uint32_t addr, SymbolTable *symtbl, SymbolTable *reltbl);

/* Helper functions in write_pass_one().*/
unsigned write_la(FILE *output, const char *name, char **args, int num_args);

unsigned write_move(FILE *output, const char *name, char **args, int num_args);

unsigned write_bgt(FILE *output, const char *name, char **args, int num_args);

unsigned write_blt(FILE *output, const char *name, char **args, int num_args);

/* Helper functions in translate_inst(). */

int write_syscall(FILE *output);

int write_muldiv(uint8_t funct, FILE *output, char **args, size_t num_args);

int write_mf(uint8_t funct, FILE *output, char **args, size_t num_args);

int write_shift(uint8_t funct, FILE *output, char **args, size_t num_args);

int write_jr(uint8_t funct, FILE *output, char **args, size_t num_args);

int write_addiu(uint8_t opcode, FILE *output, char **args, size_t num_args);

int write_ori(uint8_t opcode, FILE *output, char **args, size_t num_args, uint32_t addr, SymbolTable *reltbl);

int write_lui(uint8_t opcode, FILE *output, char **args, size_t num_args, uint32_t addr, SymbolTable *reltbl);

int write_mem(uint8_t opcode, FILE *output, char **args, size_t num_args);

int write_branch(uint8_t opcode, FILE *output, char **args, size_t num_args,
                 uint32_t addr, SymbolTable *symtbl);

int write_jump(uint8_t opcode, FILE *output, char **args, size_t num_args,
               uint32_t addr, SymbolTable *reltbl);

/* 处理R型算术和逻辑指令 */
int write_rtype(uint8_t funct, FILE *output, char **args, size_t num_args);

#endif
