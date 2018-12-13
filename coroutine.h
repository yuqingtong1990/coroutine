#ifndef _COROUTINE_H_
#define _COROUTINE_H_

/*
*C语言跨平台纤程库
*@author:yuqingtong
*@email:yuqingtong1990@gmail.com
*@date:2018.12.13
*/

/**
纤程存在状态
*/
typedef enum costatus{       
	CS_Dead = 0,        // 纤程死亡状态
	CS_Ready = 1,       // 纤程已经就绪
	CS_Running = 2,     // 纤程正在运行
	CS_Suspend = 3,     // 纤程暂停等待
}costatus_e;

typedef struct comng* comng_t;

/*
* 创建运行纤程的主体, 等同于纤程创建需要执行的函数体.
* schedule : co_start 函数返回的结果
* ud       : 用户自定义数据
*/
typedef void(*coroutine_fuc)(comng_t comng, void * ud);

/*
* 开启纤程系统, 并创建主纤程
*            : 返回开启的纤程调度系统管理器
*/
extern comng_t coroutine_start(void);

/*
* 关闭开启的纤程系统
* comng    : co_start 返回的纤程管理器
*/
extern void coroutine_close(comng_t comng);

/*
* 创建一个纤程对象,并返回创建纤程的id. 创建好的纤程状态是CS_Ready
* comng    : co_start 返回的纤程管理器
* func     : 纤程运行的主体
* ud       : 用户传入的数据, co_f 中 ud 会使用
*          : 返回创建好的纤程标识id
*/
extern int coroutine_create(comng_t comng, coroutine_fuc func, void * ud);

/*
* 激活创建的纤程对象.
* comng    : 纤程管理器对象
* id       : co_create 创建的纤程对象
*/
extern void coroutine_resume(comng_t comng, int id);

/*
* 中断当前运行的的纤程, 并将CPU交给主纤程处理调度.
* comng    : 纤程管理器对象
*/
extern void coroutine_yield(comng_t comng);

/*
* 得到当前纤程运行的状态
* comng    : 纤程管理器对象
* id       : co_create 创建的纤程对象
*          : 返回状态具体参照 costatus_e
*/
extern costatus_e coroutine_status(comng_t comng, int id);

/*
* 得到当前纤程系统中运行的纤程, 返回 < 0表示没有纤程在运行
* comng    : 纤程管理器对象
*          : 返回当前运行的纤程标识id,
*/
extern int coroutine_running(comng_t comng);

#endif
