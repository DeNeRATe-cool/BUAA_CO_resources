# Logisim

## 快捷方式

- `方向键` ：选中引脚之后按下，可以快速改变引脚的朝向
- `Ctrl + D` ：选中对象后按下，创造一个副本
- `Alt + 数字键` ：选中引脚后按下，改变引脚的数位
- `数字键` ：选中逻辑门后按下，快速修改逻辑门的引脚数目

## 封装子电路

- 修改默认封装
- 调整矩形边框
- 调整引脚位置
- 增加引脚说明
- 快捷键使用
  - `Ctrl + Shift + 鼠标拖拽` 保证器件在格点
  - `按住Shift拖拽` 边框保持正多边形

## 电路图示

![image-20240915221537967](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240915221537967.png)

## 自动生成电路

通过**电路分析**功能设置表达式或者真值表或者卡诺图生成电路

> 不能适用输入引脚过多的情况

## 组件延迟和险象

- 组件存在一定的延迟，故多个信号虽然理论同时到达，但实际上并不是，会存在信号有误的情况
- 如下图，计数器可以计数，但最终的输出端结果永远为0，因为存在一定时间（极短时间）与门结果为1，
- 通过 `Ctrl + E` 取消自动模拟信号后通过 `Ctrl + I` 开启单步传输即可详细了解每部进程的影响

![image-20240916133824956](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916133824956.png)

`Ctrl + I` 看出延迟的影响：

![image-20240916134459984](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916134459984.png)

可通过增加**缓冲器（增加一级延迟）**来避免险象的发生！

（但在实际电路中这种方法是不可取的）

## 震荡现象

（循环次数达到Logisim设定阈值后，将自动退出，判断出现**震荡现象**）

- 输入为0时不会出现问题
- 输入为1时

![image-20240916143554811](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916143554811.png)

（进入无限的循环）

![image-20240916145019023](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916145019023.png)

## Logisim线路库

**线路**

![image-20240916145122013](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916145122013.png)

**组件通用属性**

![image-20240916150432778](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916150432778.png)

**分线器 splitter**

![image-20240916150900760](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916150900760.png)

实例展示

![image-20240916151241583](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916151241583.png)

**探针 Probe**

**==便于调试==**

![image-20240916152604226](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916152604226.png)

**隧道 Tunnel**

通过标签的方式进行远距离连接

![image-20240916152859178](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916152859178.png)

**上/下拉电阻 Pull Resistor**

可将**不确定的输入**变为**给定值**

![image-20240916153223476](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916153223476.png)

**位扩展器**

![image-20240916153405957](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916153405957.png)

## Logisim逻辑门库、复用器库

**逻辑门库**

![image-20240916153624737](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916153624737.png)

**三态门、三态非门**

![image-20240916153837328](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916153837328.png)

**复用器库**

![image-20240916153843287](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916153843287.png)

**多路选择器 MUX**

> 不要**滥用多路选择器**来代替**逻辑电路**，会增大电路延迟！

- 位宽为 $n$，输入端有 $2 ^ n$ 个
- 使能端为1时可以进行输出
- 选择端控制选择哪个输入进行输出

![image-20240916153926907](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916153926907.png)

**解复用器 DMX**

![image-20240916154424017](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916154424017.png)

**解码器 Decoder**

$n$ 位的选择端翻译为 $2 ^ n$ 个最小项

![image-20240916154523027](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916154523027.png)

**优先编码器 Priority Encoder**

将 $2 ^ n$ 个输入的**优先级最高**请求编码为输出端

e.g. 第一个最高级为 6，输出 `110`

![image-20240916154742325](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916154742325.png)

## Logisim运算器库

![image-20240916154927376](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916154927376.png)

**加法器**

提供**进位输入**和**进位输出**

![image-20240916155239436](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916155239436.png)**减法器**

提供**借位输入**和**借位输出**

![image-20240916155602185](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916155602185.png)

**乘法器**

**乘积低位**和**乘积高位（进位输出）**分开保留

![image-20240916155638916](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916155638916.png)

**除法器**

![image-20240916155809604](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916155809604.png)

**求补器**

![image-20240916155940665](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916155940665.png)

**比较器**

![image-20240916155951363](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240916155951363.png)

## Logisim存储库

![image-20240918183636897](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918183636897.png)

**触发器组件**

均包含**异步置位**、**使能端**以及**异步清零**

![image-20240918183722517](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918183722517.png)

**寄存器 Register**

![image-20240918184135124](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918184135124.png)

实现**同步清零**设计

![image-20240918184732777](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918184732777.png)

**计数器**

![image-20240918184741900](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918184741900.png)

![image-20240918192711481](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918192711481.png)

**移位寄存器**

![image-20240918192823260](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918192823260.png)

**ROM**

用于存放**不需要修改的数据**

![image-20240918192932064](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918192932064.png)

**RAM**

推荐使用**输入输出分离同步模式**

![image-20240918193247588](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918193247588.png)

## Logisim输入输出库

![image-20240918193803904](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918193803904.png)

**键盘、哑终端**

![image-20240918193846185](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918193846185.png)

**7段数码管**

![image-20240918194005923](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918194005923.png)

**16进制显示数码管**

通过4位二进制显示

![image-20240918194232786](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918194232786.png)

**LED矩阵**

![image-20240918194354390](C:\Users\12298\AppData\Roaming\Typora\typora-user-images\image-20240918194354390.png)

