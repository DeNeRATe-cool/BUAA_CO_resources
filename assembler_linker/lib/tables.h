/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * tables.h
 *****************************************************************/

#ifndef TABLES_H
#define TABLES_H

#include <stdio.h>
#include <stdint.h>

extern const int SYMTBL_NON_UNIQUE;  // allows duplicate names in table
extern const int SYMTBL_UNIQUE_NAME; // duplicate names not allowed

/*
 * Defined SymbolTable. Create your own or use this to implement the following
 * functions. You are free to declare additional structs or functions.
 */

typedef struct
{
    char *name;
    uint32_t addr;
} Symbol;

typedef struct
{
    Symbol *tbl;
    uint32_t len;
    uint32_t cap;
    int mode;
} SymbolTable;

/*
 * Helper functions.
 */

/*
 * Function: allocation_failed
 *
 * Description:
 *  A suggested helper function for handling memory allocation failures.
 *
 * Returns: void
 */
void allocation_failed();

/*
 * Function: addr_alignment_incorrect
 *
 * Description:
 *  A suggested helper function for handling alignment errors.
 *
 * Returns: void
 */
void addr_alignment_incorrect();

/*
 * Function: name_already_exists
 *
 * Description:
 *  A suggested helper function for handling duplicate names.
 *
 * Parameters:
 *  name: the name that was duplicated.
 *
 * Returns: void
 */
void name_already_exists(const char *name);

/*
 * Function: write_symbol
 *
 * Description:
 *  Writes the symbol name and address to the given output stream.
 *
 * Parameters:
 *  output: the output stream to write to.
 *  addr: the address of the symbol.
 *  name: the name of the symbol.
 *
 * Returns: void
 */
void write_symbol(FILE *output, uint32_t addr, const char *name);

/*
 * Symbol Table Functions.
 */

/*
 * Function: create_table
 *
 * Description:
 *  Creates a new SymbolTable containg 0 elements and returns a pointer to that
 *  table. Multiple SymbolTables may exist at the same time.
 *  If memory allocation fails, you should call allocation_failed().
 *  Mode will be either SYMTBL_NON_UNIQUE or SYMTBL_UNIQUE_NAME. You will need
 *  to store this value for use during add_to_table().
 *
 * Parameters:
 *  mode: either SYMTBL_NON_UNIQUE or SYMTBL_UNIQUE_NAME
 *
 * Returns: SymbolTable*
 */
SymbolTable *create_table(int mode);

/*
 * Function: free_table
 *
 * Description:
 *  Frees the given SymbolTable and all associated memory.
 *
 * Parameters:
 *  table: the SymbolTable to be freed.
 *
 * Returns: void
 */
void free_table(SymbolTable *table);

/*
 * Function: add_to_table
 *
 * Description:
 *  Adds a new symbol and its address to the SymbolTable pointed to by TABLE.
 *
 * Parameters:
 *  table: a pointer to the SymbolTable structure.
 *      The SymbolTable must be able to resize itself as more elements are added.
 *  name: the label being added to the symbol table.
 *      Note that NAME may point to a temporary array, so it is not safe to simply
 *      store the NAME pointer. You must store a copy of the given string.
 *  addr: the byte offset from the first instruction.
 *
 * Returns: int
 *  If ADDR is not word-aligned, you should call addr_alignment_incorrect() and
 *  return -1. If the table's mode is SYMTBL_UNIQUE_NAME and NAME already exists
 *  in the table, you should call name_already_exists() and return -1. If memory
 *  allocation fails, you should call allocation_failed().
 *  Otherwise, you should store the symbol name and address and return 0.
 */
int add_to_table(SymbolTable *table, const char *name, uint32_t addr);

/*
 * Function: get_addr_for_symbol
 *
 * Description:
 *  Returns the address (byte offset) of the given symbol. If a symbol with name
 *  NAME is not present in TABLE, return -1.
 *
 * Parameters:
 *  table: a pointer to the SymbolTable structure.
 *  name: the symbol name to look up.
 *
 * Returns: int64_t
 *  The address of the symbol, or -1 if the symbol is not present in the table.
 */
int64_t get_addr_for_symbol(SymbolTable *table, const char *name);

/*
 * Function: get_symbol_for_addr
 *
 * Description:
 *  Returns the address symbol name of the given address (byte offset). If a symbol
 *  with address ADDR is not present in TABLE, return NULL.
 *
 * Parameters:
 *  table: a pointer to the SymbolTable structure.
 *  addr: the symbol address to look up.
 *
 * Returns: const char*
 *  The symbol name, or NULL if the symbol is not present in the table.
 */
const char *get_symbol_for_addr(SymbolTable *table, const int32_t addr);

/*
 * Function: write_table
 *
 * Description:
 *  Writes the SymbolTable TABLE to OUTPUT.
 *
 * Parameters:
 *  table: a pointer to the SymbolTable structure.
 *  output: the output stream to write to.
 *
 * Returns: void
 */
void write_table(SymbolTable *table, FILE *output);

#endif