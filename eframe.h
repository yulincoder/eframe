#ifndef __EFRAME_H__
#define  __EFRAME_H__

typedef unsigned int u16;  
typedef unsigned char u8;
typedef u8 PROC;

/*EN
 *
 */
 
/*CH
 * 这决定了每个事件的响应函数的返回值都必须是PROC(u8)类型。。
 * 日后可能需要加入响应函数的上下文机制，同步机制，到时候得要有返回值。
 */
typedef PROC (*PROCTYPE)(void);   
#define MAX_PROC_AMOUNT 10 // 最大处理事件过程数量


// 预定义事件类型, 具体事件变量需要使用event_bind(e, n)与预定义事件绑定
// 因为框架内部都使用预定义事件类型,
typedef enum EVENT_NUM {
  NULL_EVENT = 0,
  EVENT_1,
  EVENT_2,
  EVENT_3,
  EVENT_4,
  EVENT_5,
  EVENT_6,
  EVENT_7,
  EVENT_8,
  EVENT_9,    
} EVENTTYPE;
  
// 这里绑定仅仅是一个赋值过程,因此事件定义需要在全局范围内
// 最后应该支持事件动态注册和删除 
#define event_bind(e, n)  e = EVENT_##n  // 设置用户定义事件绑定到预定义事件

/* 响应函数返回的状态码 */
#define DEFAULT 0  //默认状态码（无意义）
#define NO_PROC 1  //没有响应函数

/**
 * 响应程序队列
 */
extern PROCTYPE  proc_queue[MAX_PROC_AMOUNT];


/**
 * 响应函数与事件绑定
 */
#define proc_bind(event, proc) \
				do{ \
					proc_queue[event] = proc; \
				}while(0)

/**
 * 获取事件对应的处理进程
 */
extern PROCTYPE get_proc(EVENTTYPE event);
extern PROC proc_null(void); // 空处理函数

/** 
 * 根据事件,调用处理事件的过程回调函数
 */
#define event_proc(event) (proc_queue[event] ? proc_queue[event] : proc_null)()
#endif // __TFRAME_H__
