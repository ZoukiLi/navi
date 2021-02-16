/*
定义虚拟CPU的相关类型和函数
*/
#ifndef CPU_H
#define CPU_H

/*
内存和操作数栈中字节长度
规定为8位无符号整数类型
*/
typedef unsigned char BYTE_TYPE;

/*
指针长度
规定为64位无符号整数类型
寻址空间大小目前仅使用低32位，高32位用于符号拓展
*/
typedef unsigned long long POINTER_TYPE;

/*
段选择子长度
规定为16位无符号整数类型
*/
typedef unsigned short SEGMENT_SELECTOR_TYPE;

/*
段寄存器类型
仅有选择子的16位可见
*/
struct segment_register
{
    /*段基址*/
    POINTER_TYPE base;
    /*段长度限制*/
    POINTER_TYPE limit;
    /*段属性*/
    SEGMENT_SELECTOR_TYPE attribute;
    /*段选择子*/
    SEGMENT_SELECTOR_TYPE selector;
};

/*段寄存器类型*/
typedef struct segment_register SEGMENT_REGISTER_TYPE;

/*
表示一个虚拟CPU的结构体类型
*/
struct cpu
{
    /*内存的首地址*/
    BYTE_TYPE *memory;

    /*
    操作数栈首地址
    操作数栈与堆栈不同，从内存低地址向高地址增长，且采用大端方式存储
    */
    BYTE_TYPE *operand_stack;

    /*64位指令指针寄存器*/
    POINTER_TYPE RIP;
    /*
    64位堆栈顶指针寄存器
    堆栈从内存高地址向低地址增长，小段方式存储
    */
    POINTER_TYPE RSP;
    /*
    64位堆栈底指针寄存器
    堆栈从内存高地址向低地址增长，小段方式存储
    */
    POINTER_TYPE RBP;

    /*
    16位段寄存器
    CS：代码段 DS：数据段 SS：堆栈段 ES：附加段
    */
    SEGMENT_REGISTER_TYPE CS,DS,SS,ES;
};

/*CPU单步运行*/
int cpu_step(cpu *, BYTE_TYPE);

#endif
