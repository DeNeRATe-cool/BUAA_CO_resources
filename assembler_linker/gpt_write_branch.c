// 有点问题，这个地方该使用 get_addr_for_symbol 获取symbol的地址
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/translate_utils.h"
#include "lib_assembler/assembler_utils.h"

/*
 * Function: write_branch
 * ----------------------
 * 处理分支指令并将其转换为十六进制机器码格式输出。
 *
 * 参数:
 *   opcode    - 分支指令的 opcode 字段
 *   output    - 输出文件指针
 *   args      - 分支指令的参数数组 (rs, rt, offset)
 *   num_args  - 参数数量
 *   addr      - 当前指令的行地址
 *   symtbl    - 符号表 (SymbolTable)
 *
 * 返回值:
 *   成功写入返回 0，错误返回 -1
 */
int write_branch(uint8_t opcode, FILE *output, char **args, size_t num_args, uint32_t addr, SymbolTable *symtbl) {
    if (num_args != 3) return -1; // 参数数量不符合要求

    int rs = translate_reg(args[0]);
    int rt = translate_reg(args[1]);
    int offset = translate_num(args[2]);

    if (rs == -1 || rt == -1 || offset == -1) return -1; // 寄存器或偏移量错误

    // 计算分支目标地址：PC + 4 + (offset << 2)
    offset = (offset - (addr + 4)) >> 2;

    if (offset < -(1 << 15) || offset >= (1 << 15)) return -1; // 偏移量超出范围

    uint32_t instr = (opcode << 26) | (rs << 21) | (rt << 16) | (offset & 0xFFFF);
    write_inst_hex(output, instr);

    return 0; // 成功
}
