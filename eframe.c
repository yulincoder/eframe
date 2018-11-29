/**************************************************
 * 嵌入式事件驱动框架
 * 目标: 1.框架支持一套较为完整的系统debug方案
 *			 4.增加一个运行时监测调试方案
 * 			 5. ...
 *
 */
#include <stdio.h> // For PC
  
 
 /*
  * @API List：
    *                       efPROC(eventname) 定义事件处理handler
	*		                ef_setevent(EVENTTYPE event, num) //设置用户事件编号
    *                       ef_bindhandler(event, handler)		//绑定事件与相响应程序
	*						handle_event(EVENTTYPE event) //根据事件执行handler函数(在eframe.h中宏定义)
	*
	* @breif: 
	*						为保证程序效率，响应程序与事件之间直接通过数组对应
	*	@todo 		改进目标：用哈希（散列函数）代替一维数组。
	*/
#include "eframe.h"	


/* handler函数都注册到此数组  */
PROCTYPE  ef_handler_list[MAX_HANDLER_AMOUNT] = {0};//事件处理函数数组
EVENTTYPE ef_eventqueue[MAX_EVENT_QUEUELEN] = {0}; // 待处理事件队列

// 事件没有对应的响应程序的时候执行该函数
efPROC(ef_handle_null)
{
  // do something to handle the event without handler
    printf("null process function\n"); // For PC
}

static u8 ef_eventqueue_idx = 0;

/* 
 * 插入一个事件到队尾,插入失败返回1,否则返回1
 */
u8 ef_event_add(EVENTTYPE e)
{ 
  if(ef_eventqueue_idx >= MAX_EVENT_QUEUELEN)
    return 1;
  
  atomic(
         ef_eventqueue[ef_eventqueue_idx++] = e;
         );
  return 0;
}

// 设计查找插入复杂度都为1的队列
EVENTTYPE ef_event_poll()
{
  if(ef_eventqueue_idx == 0)
    return EFNONE_EVENT;
  return ef_eventqueue[ef_eventqueue_idx];
}
