#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/translate_utils.h"
#include "lib_assembler/assembler_utils.h"

/*
 * Function: write_remu
 * --------------------
 * 扩展 remu 伪指令：将 rs 和 rt 寄存器的值进行无符号除法，
 * 并将余数存储到 rd 寄存器。
 *
 * 参数:
 *   output    - 输出文件指针
 *   name      - 指令名称 (remu)
 *   args      - 指令参数数组 (rd, rs, rt)
 *   num_args  - 参数数量
 *
 * 返回值:
 *   成功写入输出文件的通用指令数, 出错返回 0
 */
unsigned write_remu(FILE *output, const char *name, char **args, int num_args) {
    if (num_args != 3) return 0; // 参数数量不符合要求

    int rd = translate_reg(args[0]); // 目标寄存器
    int rs = translate_reg(args[1]); // 源寄存器1
    int rt = translate_reg(args[2]); // 源寄存器2

    if (rd == -1 || rs == -1 || rt == -1) return 0; // 寄存器名非法

    // 扩展为两条通用指令：divu 和 mfhi
    fprintf(output, "divu %s, %s\n", args[1], args[2]);
    fprintf(output, "mfhi %s\n", args[0]);
    return 2; // 成功写入两条指令
}
