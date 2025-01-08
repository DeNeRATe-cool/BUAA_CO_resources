/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_assembler_utils.c
 * Assembler Submission
 *****************************************************************/

#include <string.h>
#include <stdlib.h>

#include "lib/translate_utils.h"
#include "lib_assembler/assembler_utils.h"
#include "my_assembler_utils.h"

/*
 * You should implement functions below.
 * Detailed information is in my_assembler_utils.h.
 */

int read_data_segment(FILE *input, SymbolTable *symtbl)
{
    int totByte = 0, isData = 0;
    char *name, *siz, *tableName;
    char ins[ASSEMBLER_BUF_SIZE];

    while(fgets(ins, ASSEMBLER_BUF_SIZE, input) != NULL) {
        skip_comment(ins); // 越过注释
        if(strncmp(ins, ".data", 5) == 0) {
            isData = 1;
            continue;
        }
        if(!isData) continue; // 判断开始处理数据段
        name = strtok(ins, ASSEMBLER_IGNORE_CHARS);
        strtok(NULL, ASSEMBLER_IGNORE_CHARS);
        siz = strtok(NULL, ASSEMBLER_IGNORE_CHARS);
        if(name == NULL) break; // 判断最后的空行
        name[strlen(name) - 1] = '\0'; // 去除':'
        if(!is_valid_label(name)) continue; // 判断是否符合命名规范
        tableName = (char *)malloc(sizeof(char) * (strlen(name) + 2)); // 算上加'%'的位置和'\0'
        strcpy(tableName, "%");
        strcat(tableName, name);
        add_to_table(symtbl, tableName, (uint32_t)totByte);
        totByte += atoi(siz);
    }
    if(isData) return totByte; // .data存在 返回正确值

    return -1;
}

unsigned write_li(FILE *output, const char *name, char **args, int num_args)
{
    if(num_args != 2) return 0; // 参数数量错误
    int num = atoi(args[1]);
    if(num >= -(1 << 15) && num < (1 << 15)) { // 在signed 16位 范围内
        fprintf(output, "addiu %s, $zero, %s\n", args[0], args[1]);
        return 1;
    } else {
        int top = (num >> 16) & 0xffff;
        int bottom = num & 0xffff;
        fprintf(output, "lui $at %d\n", top);
        fprintf(output, "ori %s $at %d\n", args[0], bottom);
        return 2;
    }
    return 0;
}

int write_rtype(uint8_t funct, FILE *output, char **args, size_t num_args)
{
    if(num_args != 3) return -1;
    int rd = translate_reg(args[0]) << 11;
    int rs = translate_reg(args[1]) << 21;
    int rt = translate_reg(args[2]) << 16;
    uint32_t ins = rs | rt | rd | funct;
    write_inst_hex(output, ins);
    return 0;
}
// /*****************************************************************
//  * MIPS汇编器指令翻译实现文件
//  * 
//  * 该文件实现了MIPS汇编指令到机器码的翻译功能，包括：
//  * - 伪指令的展开
//  * - R型指令的翻译
//  * - I型指令的翻译
//  * - J型指令的翻译
//  * - 内存访问指令的处理
//  *****************************************************************/

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// #include "translate.h"
// #include "tables.h"
// #include "utils.h"

// /* 第一遍扫描时的指令写入函数
//  * 参数:
//  *   output: 输出文件指针
//  *   name: 指令名称
//  *   args: 指令参数数组
//  *   num_args: 参数个数
//  * 返回值:
//  *   写入的指令数量，失败返回0
//  */
// unsigned write_pass_one(FILE *output, const char *name, char **args, int num_args) {
//     // 处理li伪指令
//     if (strcmp(name, "li") == 0) {
//         if (num_args != 2) return 0;
        
//         // 解析立即数
//         int32_t imm;
//         if (translate_num(&imm, args[1], 0, 32) == -1) return 0;
        
//         // 如果立即数在16位范围内，使用单个addiu指令
//         if (imm >= -32768 && imm <= 32767) {
//             fprintf(output, "addiu %s $0 %d\n", args[0], imm);
//             return 1;
//         } else {
//             // 否则需要使用lui和ori的组合
//             uint32_t upper = (imm >> 16) & 0xFFFF;
//             uint32_t lower = imm & 0xFFFF;
//             fprintf(output, "lui $at %d\n", upper);
//             fprintf(output, "ori %s $at %d\n", args[0], lower);
//             return 2;
//         }
//     }
//     // 处理其他伪指令
//     else if (strcmp(name, "la") == 0) {
//         return write_la(output, name, args, num_args);
//     }
//     else if (strcmp(name, "move") == 0) {
//         return write_move(output, name, args, num_args);
//     }
//     else if (strcmp(name, "bgt") == 0) {
//         return write_bgt(output, name, args, num_args);
//     }
//     else if (strcmp(name, "blt") == 0) {
//         return write_blt(output, name, args, num_args);
//     }
    
//     // 对于普通指令，直接写入
//     write_inst_string(output, name, args, num_args);
//     return 1;
// }

// /* 将指令翻译为机器码
//  * 参数:
//  *   output: 输出文件指针
//  *   name: 指令名称
//  *   args: 指令参数数组
//  *   num_args: 参数个数
//  *   addr: 当前指令地址
//  *   symtbl: 符号表
//  *   reltbl: 重定位表
//  * 返回值:
//  *   成功返回0，失败返回-1
//  */
// int translate_inst(FILE *output, const char *name, char **args, size_t num_args,
//                   uint32_t addr, SymbolTable *symtbl, SymbolTable *reltbl) {
//     // 系统调用指令
//     if (strcmp(name, "syscall") == 0) 
//         return write_syscall(output);
    
//     // R型指令处理
//     if (strcmp(name, "mult") == 0)
//         return write_muldiv(0x18, output, args, num_args);
//     if (strcmp(name, "div") == 0)
//         return write_muldiv(0x1A, output, args, num_args);
//     if (strcmp(name, "mfhi") == 0)
//         return write_mf(0x10, output, args, num_args);
//     if (strcmp(name, "mflo") == 0)
//         return write_mf(0x12, output, args, num_args);
//     if (strcmp(name, "sll") == 0)
//         return write_shift(0x00, output, args, num_args);
//     if (strcmp(name, "srl") == 0)
//         return write_shift(0x02, output, args, num_args);
//     if (strcmp(name, "jr") == 0)
//         return write_jr(0x08, output, args, num_args);
        
//     // I型指令处理
//     if (strcmp(name, "addiu") == 0)
//         return write_addiu(0x09, output, args, num_args);
//     if (strcmp(name, "ori") == 0)
//         return write_ori(0x0D, output, args, num_args, addr, reltbl);
//     if (strcmp(name, "lui") == 0)
//         return write_lui(0x0F, output, args, num_args, addr, reltbl);
//     if (strcmp(name, "lw") == 0)
//         return write_mem(0x23, output, args, num_args);
//     if (strcmp(name, "sw") == 0)
//         return write_mem(0x2B, output, args, num_args);
//     if (strcmp(name, "beq") == 0)
//         return write_branch(0x04, output, args, num_args, addr, symtbl);
//     if (strcmp(name, "bne") == 0)
//         return write_branch(0x05, output, args, num_args, addr, symtbl);
        
//     // J型指令处理
//     if (strcmp(name, "j") == 0)
//         return write_jump(0x02, output, args, num_args, addr, reltbl);
//     if (strcmp(name, "jal") == 0)
//         return write_jump(0x03, output, args, num_args, addr, reltbl);
        
//     // 添加新的R型指令处理
//     if (strcmp(name, "add") == 0)
//         return write_rtype(0x20, output, args, num_args);
//     if (strcmp(name, "addu") == 0)
//         return write_rtype(0x21, output, args, num_args);
//     if (strcmp(name, "sub") == 0)
//         return write_rtype(0x22, output, args, num_args);
//     if (strcmp(name, "subu") == 0)
//         return write_rtype(0x23, output, args, num_args);
//     if (strcmp(name, "multu") == 0)
//         return write_muldiv(0x19, output, args, num_args);
//     if (strcmp(name, "divu") == 0)
//         return write_muldiv(0x1B, output, args, num_args);
//     if (strcmp(name, "slt") == 0)
//         return write_rtype(0x2A, output, args, num_args);
//     if (strcmp(name, "sltu") == 0)
//         return write_rtype(0x2B, output, args, num_args);
//     if (strcmp(name, "or") == 0)
//         return write_rtype(0x25, output, args, num_args);
//     if (strcmp(name, "and") == 0)
//         return write_rtype(0x24, output, args, num_args);
        
//     // 添加新的I型内存访问指令
//     if (strcmp(name, "sb") == 0)
//         return write_mem(0x28, output, args, num_args);
//     if (strcmp(name, "lb") == 0)
//         return write_mem(0x20, output, args, num_args);
//     if (strcmp(name, "lbu") == 0)
//         return write_mem(0x24, output, args, num_args);
    
//     return -1;
// }

// /* 处理乘除法指令 (mult/div)
//  * 机器码格式: 000000 | rs(5) | rt(5) | 00000 | 00000 | funct(6)
//  */
// int write_muldiv(uint8_t funct, FILE *output, char **args, size_t num_args) {
//     if (num_args != 2) return -1;
    
//     // 解析源寄存器
//     int rs = translate_reg(args[0]);
//     int rt = translate_reg(args[1]);
//     if (rs == -1 || rt == -1) return -1;
    
//     // 构造指令，乘除法指令的rd和shamt字段为0
//     uint32_t instruction = (rs << 21) | (rt << 16) | funct;
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理从HI/LO寄存器移动数据的指令 (mfhi/mflo)
//  * 机器码格式: 000000 | 00000 | 00000 | rd(5) | 00000 | funct(6)
//  */
// int write_mf(uint8_t funct, FILE *output, char **args, size_t num_args) {
//     if (num_args != 1) return -1;
    
//     // 解析目标寄存器
//     int rd = translate_reg(args[0]);
//     if (rd == -1) return -1;
    
//     // 构造指令，rs和rt字段为0
//     uint32_t instruction = (rd << 11) | funct;
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理移位指令 (sll/srl)
//  * 机器码格式: 000000 | 00000 | rt(5) | rd(5) | shamt(5) | funct(6)
//  */
// int write_shift(uint8_t funct, FILE *output, char **args, size_t num_args) {
//     if (num_args != 3) return -1;
    
//     // 解析寄存器和移位量
//     int rd = translate_reg(args[0]);
//     int rt = translate_reg(args[1]);
//     int shamt;
//     if (translate_num(&shamt, args[2], 0, 5) == -1) return -1;
    
//     if (rd == -1 || rt == -1) return -1;
    
//     // 构造指令
//     uint32_t instruction = (rt << 16) | (rd << 11) | (shamt << 6) | funct;
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理寄存器跳转指令 (jr)
//  * 机器码格式: 000000 | rs(5) | 00000 | 00000 | 00000 | funct(6)
//  */
// int write_jr(uint8_t funct, FILE *output, char **args, size_t num_args) {
//     if (num_args != 1) return -1;
    
//     // 解析源寄存器
//     int rs = translate_reg(args[0]);
//     if (rs == -1) return -1;
    
//     // 构造指令，rt、rd和shamt字段为0
//     uint32_t instruction = (rs << 21) | funct;
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理立即数加法指令 (addiu)
//  * 机器码格式: opcode(6) | rs(5) | rt(5) | immediate(16)
//  */
// int write_addiu(uint8_t opcode, FILE *output, char **args, size_t num_args) {
//     if (num_args != 3) return -1;
    
//     // 解析寄存器和立即数
//     int rt = translate_reg(args[0]);
//     int rs = translate_reg(args[1]);
//     int imm;
//     if (translate_num(&imm, args[2], -32768, 32767) == -1) return -1;
    
//     if (rt == -1 || rs == -1) return -1;
    
//     // 构造指令
//     uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF);
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理按位或立即数指令 (ori)
//  * 机器码格式: opcode(6) | rs(5) | rt(5) | immediate(16)
//  */
// int write_ori(uint8_t opcode, FILE *output, char **args, size_t num_args, 
//               uint32_t addr, SymbolTable *reltbl) {
//     if (num_args != 3) return -1;
    
//     // 解析寄存器
//     int rt = translate_reg(args[0]);
//     int rs = translate_reg(args[1]);
//     int imm;
    
//     if (rt == -1 || rs == -1) return -1;
    
//     // 处理立即数或符号
//     if (translate_num(&imm, args[2], 0, 65535) == -1) {
//         // 如果不是立即数，添加到重定位表
//         add_to_table(reltbl, args[2], addr);
//         imm = 0;
//     }
    
//     // 构造指令
//     uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF);
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理加载高位立即数指令 (lui)
//  * 机器码格式: opcode(6) | 00000 | rt(5) | immediate(16)
//  */
// int write_lui(uint8_t opcode, FILE *output, char **args, size_t num_args,
//               uint32_t addr, SymbolTable *reltbl) {
//     if (num_args != 2) return -1;
    
//     // 解析目标寄存器
//     int rt = translate_reg(args[0]);
//     int imm;
    
//     if (rt == -1) return -1;
    
//     // 处理立即数或符号
//     if (translate_num(&imm, args[1], 0, 65535) == -1) {
//         add_to_table(reltbl, args[1], addr);
//         imm = 0;
//     }
    
//     // 构造指令，rs字段为0
//     uint32_t instruction = (opcode << 26) | (rt << 16) | (imm & 0xFFFF);
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理内存访问指令 (lw/sw)
//  * 机器码格式: opcode(6) | rs(5) | rt(5) | offset(16)
//  * 支持两种格式:
//  * 1. lw/sw rt, offset(rs)    - 直接的偏移量访问
//  * 2. lw/sw rt, Label(rs)     - 基于标签的访问，需要重定位
//  */
// int write_mem(uint8_t opcode, FILE *output, char **args, size_t num_args) {
//     // 检查参数数量是否为2 (目标寄存器和内存地址)
//     if (num_args != 2) return -1;
    
//     // 解析目标寄存器rt (lw指令的目的寄存器或sw指��的源寄存器)
//     int rt = translate_reg(args[0]);
//     if (rt == -1) return -1;
    
//     // 复制内存地址字符串，因为strtok会修改原字符串
//     char *mem_addr = strdup(args[1]);
//     if (!mem_addr) return -1;  // 内存分配失败
    
//     // 解析内存地址格式：offset(base_reg) 或 Label(base_reg)
//     char *offset_str = strtok(mem_addr, "()");  // 获取偏移量或标签字符串
//     char *reg_str = strtok(NULL, "()");         // 获取寄存器字符串
    
//     // 检查解析是否成功
//     if (!offset_str || !reg_str) {
//         free(mem_addr);
//         return -1;
//     }
    
//     // 解析基址寄存器rs
//     int rs = translate_reg(reg_str);
//     if (rs == -1) {
//         free(mem_addr);
//         return -1;
//     }
    
//     int offset = 0;
//     // 尝试将offset_str解析为数字
//     if (translate_num(&offset, offset_str, -32768, 32767) == -1) {
//         // 如果不是数字，说明是标签
//         // 创建标签名+"@Lo"的新字符串
//         char *label_name = malloc(strlen(offset_str) + 4); // 3个字符"@Lo"加上'\0'
//         if (!label_name) {
//             free(mem_addr);
//             return -1;
//         }
//         sprintf(label_name, "%s@Lo", offset_str);
        
//         // 添加到重定位表
//         add_to_table(reltbl, label_name, addr);
        
//         // 释放临���字符串
//         free(label_name);
        
//         // 对于需要重定位的情况，offset设为0
//         offset = 0;
//     }
    
//     // 构造指令
//     uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (offset & 0xFFFF);
//     write_inst_hex(output, instruction);
    
//     // 释放临时分配的内存
//     free(mem_addr);
//     return 0;
// }

// /* 处理条件分支指令 (beq/bne)
//  * 机器码格式: opcode(6) | rs(5) | rt(5) | offset(16)
//  */
// int write_branch(uint8_t opcode, FILE *output, char **args, size_t num_args,
//                 uint32_t addr, SymbolTable *symtbl) {
//     if (num_args != 3) return -1;
    
//     // 解析比较的寄存器
//     int rs = translate_reg(args[0]);
//     int rt = translate_reg(args[1]);
//     if (rs == -1 || rt == -1) return -1;
    
//     // 计算分支目标地址
//     int label_addr;
//     if (get_addr_for_symbol(symtbl, args[2], &label_addr) == -1) return -1;
    
//     // 计算相对偏移量（以字为单位）
//     int32_t offset = (label_addr - addr - 4) >> 2;
//     if (offset > 32767 || offset < -32768) return -1;
    
//     // 构造指令
//     uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (offset & 0xFFFF);
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理无条件跳转指令 (j/jal)
//  * 机器码格式: opcode(6) | target(26)
//  */
// int write_jump(uint8_t opcode, FILE *output, char **args, size_t num_args,
//                uint32_t addr, SymbolTable *reltbl) {
//     if (num_args != 1) return -1;
    
//     // 添加跳转目标到重定位表
//     add_to_table(reltbl, args[0], addr);
    
//     // 构造指令，目标地址字段在链接时填充
//     uint32_t instruction = (opcode << 26);
//     write_inst_hex(output, instruction);
//     return 0;
// }

// /* 处理R型算术和逻辑指令
//  * 机器码格式: 000000 | rs(5) | rt(5) | rd(5) | 00000 | funct(6)
//  * 包括: add, addu, sub, subu, slt, sltu, or, and
//  */
// int write_rtype(uint8_t funct, FILE *output, char **args, size_t num_args) {
//     if (num_args != 3) return -1;
    
//     // 解析寄存器
//     int rd = translate_reg(args[0]);
//     int rs = translate_reg(args[1]);
//     int rt = translate_reg(args[2]);
    
//     if (rd == -1 || rs == -1 || rt == -1) return -1;
    
//     // 构造指令
//     uint32_t instruction = (rs << 21) | (rt << 16) | (rd << 11) | funct;
//     write_inst_hex(output, instruction);
//     return 0;
// } 

// fff
// unsigned write_remu(FILE *output, const char *name, char **args, int num_args){
//     if(num_args!=3){
//       return 0;
//     }
//     fprintf(output, "divu %s, %s\n", args[1], args[2]);
//     fprintf(output, "mfhi %s\n", args[0]);
//     return 2;
// }
// int write_branch(uint8_t opcode, FILE *output, char **args, size_t num_args,uint32_t addr, SymbolTable *symtbl){
//   if(num_args!=3){
//     return 0;
//   }
//   int rs = translate_reg(args[0])<<21;
//   int rt = translate_reg(args[1])<<16;
//   int offset = (((get_addr_for_symbol(symtbl,args[2])&0xffff)-addr-4)>>2);
//   uint32_t  instr = (opcode<<26)|rs|rt|offset;
//   write_inst_hex(output,instr);
//   return 0;
// }
// int write_mem(uint8_t opcode, FILE *output, char **args, size_t num_args, uint32_t addr, SymbolTable *reltbl){
//     // 检查参数数量是否为2 (目标寄存器和内存地址)
//     if (num_args != 3) return -1;
    
//     // 解析目标寄存器rt (lw指令的目的寄存器或sw指令的源寄存器)
//     int rt = translate_reg(args[0]);
//     if (rt == -1) return -1;
//     int rs = translate_reg(args[2]);
//     if(rs==-1)return -1;
//     // 复制内存地址字符串，因为strtok会修改原字符串
//     uint32_t tmp = atoi(args[2]);
//     if(tmp<32768&&tmp>=-32768){
//       uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (tmp & 0xFFFF);
//       write_inst_hex(output, instruction);
//     }else{
//       char* label =(char*)malloc(sizeof(char)*strlen(args[1])+4);
//       strcpy(label,args[1]);
//       strcat(label,"@Lo");
//       add_to_table(reltbl,label,addr);
//       tmp = 0;
//       uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (tmp & 0xFFFF);
//       write_inst_hex(output,instruction);
//     }
//     return 0;
// }
// int write_jump(uint8_t opcode, FILE *output, char **args, size_t num_args, uint32_t addr, SymbolTable *reltbl) {
//     if (num_args != 1) {
//         return -1; // 参数数量不匹配，返回 -1 表示错误
//     }

//     // 解析目标地址（目标标签或直接地址）
//     uint32_t target_addr;
//     if (is_valid_label(args[0])) {
//         // 如果是标签，则从符号表获取地址
//         target_addr = get_addr_for_symbol(reltbl, args[0]);
//     } else {
//         // 如果是直接地址，则转换为整数
//         target_addr = strtoul(args[0], NULL, 0);
//     }

//     // 计算 26 位的目标偏移量（当前指令地址的高 4 位 + 目标地址的低 26 位）
//     uint32_t target = (target_addr >> 2) & 0x03FFFFFF;

//     // 生成 jump 指令
//     uint32_t instr = (opcode << 26) | target;

//     // 输出指令的机器码（十六进制格式）
//     write_inst_hex(output, instr);

//     return 0; // 成功，返回 0
// }
// int write_syscall(FILE *output) {
//     // syscall 指令属于 R-type 指令
//     uint32_t instr = 0x0;  // 操作码是 000000，即 0x0
//     instr |= (0xC << 6);    // 设置功能码为 0xC（syscall）

//     // 输出指令的机器码（十六进制格式）
//     write_inst_hex(output, instr);

//     return 0;  // 返回 0，表示指令已成功写入
// }
// int write_lui(uint8_t opcode, FILE *output, char **args, size_t num_args, uint32_t addr, SymbolTable *reltbl) {
//     // 检查参数数量是否为2（目标寄存器和立即数）
//     if (num_args != 2) {
//         return -1;  // 参数数量不正确，返回错误
//     }

//     // 解析目标寄存器rt
//     int rt = translate_reg(args[0]);
//     if (rt == -1) {
//         return -1;  // 如果寄存器无效，返回错误
//     }

//     // 解析立即数
//     int immediate = atoi(args[1]);

//     // 处理大于16位的立即数：需要进行符号表的重定位
//     if (immediate < -32768 || immediate >= 32768) {
//         // 如果立即数大于16位，需要进行符号表查找（通过Lo和Hi进行分离）
//         char *label = (char *)malloc(sizeof(char) * (strlen(args[1]) + 4));
//         strcpy(label, args[1]);
//         strcat(label, "@Hi");

//         // 在符号表中加入该符号的地址
//         add_to_table(reltbl, label, addr);

//         // 生成lui指令，将高16位加载到目标寄存器
//         uint32_t instr = (opcode << 26) | (rt << 16) | ((immediate >> 16) & 0xFFFF);
//         write_inst_hex(output, instr);

//         // 释放分配的内存
//         free(label);

//         return 1;  // 返回成功
//     } else {
//         // 如果立即数在16位范围内，可以直接处理
//         uint32_t instr = (opcode << 26) | (rt << 16) | (immediate & 0xFFFF);
//         write_inst_hex(output, instr);
//         return 1;  // 返回成功
//     }
// }
// int write_shift(uint8_t funct, FILE *output, char **args, size_t num_args)
// {
//     // 确保参数数量为 3：目标寄存器、源寄存器、移位量
//     if (num_args != 3) {
//         return -1;  // 参数数量错误，返回错误
//     }

//     // 解析目标寄存器rd
//     int rd = translate_reg(args[0]);
//     if (rd == -1) {
//         return -1;  // 无效寄存器，返回错误
//     }

//     // 解析源寄存器rt
//     int rt = translate_reg(args[1]);
//     if (rt == -1) {
//         return -1;  // 无效寄存器，返回错误
//     }

//     // 解析移位量shamt
//     int shamt = atoi(args[2]);
//     if (shamt < 0 || shamt > 31) {
//         return -1;  // 移位量无效，必须在 0 到 31 之间
//     }

//     // 生成指令：{opcode(6 bit)} {rs(5 bit)} {rt(5 bit)} {rd(5 bit)} {shamt(5 bit)} {funct(6 bit)}
//     uint32_t instr = (0 << 26) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    
//     // 写入输出文件
//     write_inst_hex(output, instr);

//     return 1;  // 成功生成并写入指令
// }