#ifndef __EFRAME_H__
#define  __EFRAME_H__
#include <stdio.h>		// For PC

typedef unsigned int ef_u16;
typedef unsigned char ef_u8;
typedef ef_u8 ef_event_t;
typedef enum {
  efSUCCESS = 0,
  efFAIL 
} ef_err_t;

#define efPROC(event) void event(void)	// 定义事件处理函数的方式
typedef void (*ef_handler_t) (void);
 
#define efMAX_HANDLER_AMOUNT 20	// 最大处理事件过程数量, 1-10为框架内置事件,因此该值至少为10, 其中各个事件为如下说明
/* 
uartdriver.h: EVENT_UART_EF 事件9
 ... 待添加
*/

  
#define efMAX_QUEUE 10
// 队列头结点为哨兵,因此实际队列长度为有效数据长度+1
#define efREAL_LEN efMAX_QUEUE + 1	// 待处理事件队列长度
    
// 0作为无事件
#define efEVENT_NULL 0
#define efEVENT_SCH 1 // default event, to launch the scheduler
#define booted main
#define main_handler main


extern ef_event_t ef_event_cnt;
// 初始化事件变量, 每次获得一个事件ID
#define ef_event_init() ef_event_cnt++ 
    
/* 响应函数返回的状态码 */ 
#define efDEFAULT 0		//默认状态码（无意义）
#define efNO_PROC 1		//没有响应函数
    
/* 响应程序队列 */ 
extern ef_handler_t ef_handler_list[efMAX_HANDLER_AMOUNT];
  
/* 响应函数与事件绑定 */ 
#define ef_bindhandler(ef_event, ef_handler) \
do {\
 ef_handler_list[ef_event] = ef_handler;\
} while (0)
 
/* 获取事件对应的处理进程 */ 
extern efPROC(ef_handle_null);	// 空处理函数

/* 根据事件,调用处理事件的过程回调函数 */ 
#define ef_handle_event(event)\
do {\
 switch(event) {\
 case 1:ef_scheduler_run();\
 default:(ef_handler_list[event] ? ef_handler_list[event] : ef_handle_null) (); \
}} while (0)

// post a synchronization event.
// Execute handler immediately upon invocation.
// Synchronization event have the highest priority.
#define ef_syncpost(event) ef_handle_event(event)

extern void ef_idle(void);

// 需要移植
// 设置原子操作,在进入时应该添加屏蔽中断代码,退出时恢复
#define ef_atomic(s) \
do {\
 printf("enter atomic regeion\n");\
 s \
 printf("exit atomic regeion\n");\
} while (0)

extern ef_err_t ef_post(ef_event_t e);
extern void ef_scheduler_run(void);

#endif // __TFRAME_H__


