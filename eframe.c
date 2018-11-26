/**************************************************
 * 嵌入式事件驱动框架
 * 目标: 1.框架支持一套较为完整的系统debug方案
 *			 2.基于事件驱动运行
 *			 3.增加支持一些WSN协议(可以是自写),，
 *     		 似乎没有(待考证)像zigbee那种一个支持802.15.4IPwsn协议的编程框架
 *				 (contiki有基于802.15.4的IPwsn协议,但contiki是操作系统)
 *			 4.增加一个运行时监测调试方案
 * 			 5. ...
 *
 * 开发注意：多多参考osal
 */
#include <stdio.h> // For PC
  
 
 /*
  * @API List：
	*						bind_proc(event,proc)		//绑定事件与相响应程序
	*						void proc_null(void)		//未绑定响应程序的事件的默认处理程序
	*						PROCTYPE event_proc(EVENTTYPE event) //获得事件的响应程序(在eframe.h中宏定义)
	*
	* @breif: 
	*						为保证程序效率，响应程序与事件之间直接通过数组对应，这样做的
	*						原因是数组可以直接通过事件找到与其对应的响应程序，没有查找过程，数组下标
	*						表示事件。如果采用队列的话，当事件很少而队列较长的话，效率会大大
	*						降低，程序的大部分时间都花在了遍历队列，查找事件对应的响应程序上
	*						了。尤其是对于WSN某些数据采集周期很长的场景，事件到来较慢，遍历队列
	*						会做很多无用功。 但是这样做有一个缺点就是事件必须按照0，1，2，。。。这样
	*						来定义。
	*
	*	@todo 		改进目标：用哈希（散列函数）代替一维数组。
	*/
#include "eframe.h"	


/* proc函数都注册到此数组  */
PROCTYPE  proc_queue[MAX_PROC_AMOUNT] = {0};//响应函数数组

// 事件没有对应的响应程序的时候执行该函数
PROC proc_null(void)
{
    printf("null process func\n"); // For PC
    return NO_PROC;
}
