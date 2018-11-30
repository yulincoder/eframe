#ifndef __EFRAME_H__
#define  __EFRAME_H__
#include <stdio.h>		// For PC

typedef unsigned int u16;
typedef unsigned char u8;
typedef u8 event_t;
typedef enum {
  SUCCESS = 0,
  FAIL 
} err_t;
 
/*CH
 * 事件handler函数为void xx(void)
 */ 
#define efPROC(event) void event(void)	// 定义事件处理函数的方式
typedef void (*handler_t) (void);
 
#define MAX_HANDLER_AMOUNT 10	// 最大处理事件过程数量
    
#define MAX_QUEUE 10
// 队列头结点为哨兵,因此实际队列长度为有效数据长度+1
#define REAL_LEN MAX_QUEUE + 1	// 待处理事件队列长度
    
// 0作为无事件
#define EFNONE_EVENT 0
static event_t event_cnt = EFNONE_EVENT;
 
// 初始化事件变量, 每次获得一个事件ID
#define ef_event_init() ++event_cnt
    
/* 响应函数返回的状态码 */ 
#define DEFAULT 0		//默认状态码（无意义）
#define NO_PROC 1		//没有响应函数
    
/* 响应程序队列 */ 
extern handler_t ef_handler_list[MAX_HANDLER_AMOUNT];
  
/* 响应函数与事件绑定 */ 
#define ef_bindhandler(event, handler) \
do {\
 ef_handler_list[event] = handler;\
} while (0)
 
/**
 * 获取事件对应的处理进程
 */ 
extern efPROC(ef_handle_null);	// 空处理函数

/* 根据事件,调用处理事件的过程回调函数 */ 
#define ef_handle_event(event)\
do {\
 (ef_handler_list[event] ? ef_handler_list[event] : ef_handle_null) ();\
} while (0)
 

// 需要移植
#define ef_idle()\
do {\
 printf("idle handler, MCU enter the halt()\n");\
} while (0)
 
// 需要移植
// 设置原子操作,在进入时应该添加屏蔽中断代码,退出时恢复
#define atomic(s) \
do {\
 printf("enter atomic regeion\n");\
 s \
 printf("exit atomic regeion\n");\
} while (0)

extern err_t ef_post(event_t e);
extern void ef_scheduler_run(void);

#endif // __TFRAME_H__


