#ifndef __TEFRAME_H__
#define  __TEFRAME_H__

typedef unsigned int u16;  
typedef unsigned char u8;
// typedef u16 EVENTTYPE;
typedef u8 PROC;

/*EN
 *
 */
 
/*CH
 * 这决定了每个事件的响应函数的返回值都必须是PROC(u8)类型。。
 * 日后可能需要加入响应函数的上下文机制，同步机制，到时候得要有返回值。
 */
typedef PROC (*PROCTYPE)(void);   
#define MAX_PROC_AMOUNT 10

/* 事件类型 */
/* 
#define EVENT_0  0
#define EVENT_1	 1 
#define EVENT_2	 2 
#define EVENT_3	 3 
#define EVENT_4	 4 
#define EVENT_5  5
#define EVENT_6	 6 
#define EVENT_7	 7 
#define EVENT_8	 8 
#define EVENT_9	 9 
*/

// 预定义事件类型, 具体事件变量需要使用event_bind(e, n)与预定义事件绑定
// 因为框架内部都使用预定义事件类型,
typedef enum EVENT_NUM {
  EVENT_0 = 0,
  EVENT_1,
  EVENT_2,
  EVENT_3,
  EVENT_4,
  EVENT_5,
  EVENT_6,  
} EVENTTYPE;
// #define EVENT_MOUNT  5   //事件数量
extern u8 EVENT_MOUNT;
#define setProcNum(n) EVENT_MOUNT = n
  
// 这里绑定仅仅是一个赋值过程,因此事件定义需要在全局范围内
// 最后应该支持事件动态注册和删除 
#define event_bind(e, n)  e = EVENT_##n

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
 * 根据事件获得对应事件处理函数
 */
#define get_proc(event) (proc_queue[event] ? proc_queue[event] : proc_null)
#endif // __TEFRAME_H__
