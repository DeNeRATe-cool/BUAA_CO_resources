# BUAA软件学院-计算机硬件基础个人资源共享

> 软件学院计组改革之后，内容相较于之前简单了许多（这里主要是针对实验部分），期末考试难度和大致考点和计院的如出一辙，参考着复习就行☺️

**关于23级实验**

- Lab1（难度：低）：**Logisim电路设计** --- 逻辑电路 + 有限状态机，好好列真值表，然后通过Logisim自带的生成器就行~
- Lab2（难度：低）：**MIPS汇编** --- 共4题，denerate在预习的时候花的时间挺多的，看了[B站上网课](https://www.bilibili.com/video/BV19J411y7pA/?spm_id_from=333.337.search-card.all.click&vd_source=d178a86a05c06cf688ae3c86d8d7f20d)然后练习了很多题目，最后上机挺基础的。看着C语言代码打MIPS汇编，一般最后一道会有一个0分的递归（课内不要求掌握），但做了可以加分~
- Lab3（难度：难）：**Cache高速缓存** --- 共2题，全靠[CSAPP实验之cache lab](https://zhuanlan.zhihu.com/p/79058089)，Cache替换策略 + $N \times M$ 矩阵转置，23级是PLRU（可以提前把所有的可能替换策略都实现一下，但感觉能考的基本这几年都考过一遍了，之后题型可能会变），矩阵是60 $\times$ 68（过的方法很魔幻，应该是没有理论最优解）
- Lab4（难度：中）：**链接与运行** --- 共3题，实现汇编过程（链接在课下实验已经做过了），会有助教自创的汇编指令，然后还有指令扩充（比如 `addi` 扩充为 `lui + ori`），准备的重点在于读读已有的所有程序代码，熟悉每一个部分是干嘛的，课下实验是由Hint的，但课上实验没有（另外，还有一个小trick：让G老师先把下发资料里边 `translate.h` 的所有汇编指令进行实现，在课上可以大有用处）

```
.
├─homework --- denerate的平时作业
├─old原题 --- 软院计组课改之前的计组期末题
├─22期末复习.md --- 22级期末复习课笔记
├─2020.pdf --- 计算机学院计组期末试题
├─2022.pdf --- 计算机学院计组期末试题
├─Digital Design and Computer Architecture 2nd edition.pdf --- rt 电子书
├─homework-answer.pdf --- 平时作业答案
├─MIPS Assembly Preparation.pdf --- denerate的MIPS上机模板
├─MIPS-Instr-doc.pdf --- rt MIPS电子文档
├─深入理解计算机系统（原书第三版）-数据优化版.pdf --- rt 电子书
├─计组2024串讲.pdf --- 期末串讲PPT
├─计组复习课.pdf --- 23级计组期末复习笔记
├─计算机硬件基础期末复习.pdf --- denerate期末复习的计组笔记
├─计算机硬件基础笔记.pdf --- denerate随堂计组学习笔记
├─Logisim --- 课上课下实验 - Lab1 Logisim电路设计
├─MIPS --- 课上课下实验 - Lab2 MIPS汇编
├─cachelab --- 课上课下实验 - Lab3 Cache高速缓存
├─assembler_linker --- 课上课下实验 - Lab4 链接与运行
└─课件 --- rt
```

> 关于**计算机硬件基础**更多优质资源可 + v
> 
> <img src="https://s2.loli.net/2025/01/08/XtGqHAxlpKQhrEY.jpg" alt="denerate" style="width: 300px; height: auto;">