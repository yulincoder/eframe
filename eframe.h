#ifndef __EFRAME_H__
#define  __EFRAME_H__

typedef unsigned int u16;  
typedef unsigned char u8;
// typedef u8 efPROC;

/*EN
 *
 */
 
/*CH
 * 这决定了每个事件的响应函数的返回值都必须是PROC(u8)类型。。
 * 日后可能需要加入响应函数的上下文机制，同步机制，到时候得要有返回值。
 */
#define efPROC(event) void event(void) // 定义事件处理函数的方式
typedef void (*PROCTYPE)(void);   

#define MAX_HANDLER_AMOUNT 10 // 最大处理事件过程数量
#define MAX_EVENT_QUEUELEN 5 // 待处理事件队列长度

// 预定义事件类型, 具体事件变量需要使用event_bind(e, n)与预定义事件绑定
// 因为框架内部都使用预定义事件类型,
typedef enum EVENT_NUM {
  EFNONE_EVENT = 0,
  EFEVENT_1,
  EFEVENT_2,
  EFEVENT_3,
  EFEVENT_4,
  EFEVENT_5,
  EFEVENT_6,
  EFEVENT_7,
  EFEVENT_8,
  EFEVENT_9,    
} EVENTTYPE;
  
// 这里绑定仅仅是一个赋值过程,因此事件定义需要在全局范围内
// 最后应该支持事件动态注册和删除 
#define ef_setevent(e, n) EVENTTYPE e = EFEVENT_##n;  // 设置用户定义事件绑定到预定义事件

/* 响应函数返回的状态码 */
#define DEFAULT 0  //默认状态码（无意义）
#define NO_PROC 1  //没有响应函数

/**
 * 响应程序队列
 */
extern PROCTYPE ef_handler_list[MAX_HANDLER_AMOUNT];


/**
 * 响应函数与事件绑定
 */
#define ef_bindhandler(event, handler) \
do { \
    ef_handler_list[event] = handler; \
   } while(0)

/**
 * 获取事件对应的处理进程
 */
extern efPROC(ef_handle_null); // 空处理函数

/** 
 * 根据事件,调用处理事件的过程回调函数
 */
#define ef_handle_event(event)\
do {\
    (ef_handler_list[event] ? ef_handler_list[event] : ef_handle_null)();\
   } while(0)

// 需要移植
#define ef_idle()\
  do{\
    printf("idle handler, MCU enter the halt()\n");\
  }while(0)

// 需要移植
// 设置原子操作,在进入时应该添加屏蔽中断代码,退出时恢复
#define atomic(s) \
  do{\
  printf("enter atomic regeion\n");\
  s \
  printf("exit atomic regeion\n");\
} while(0)


extern u8 ef_event_add(EVENTTYPE e);
#endif // __TFRAME_H__
