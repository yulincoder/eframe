#include <stdio.h>
#include "teframe.h"

/* 
#define EVENT_KEYSCAN  EVENT_0 
#define EVENT_TIMER	 EVENT_1 
#define EVENT_LCD	 EVENT_2 
#define EVENT_MOTOR  EVENT_3
#define EVENT_BEEZ  EVENT_4 
*/
/* 需要定义在全局 */
EVENTTYPE EVENT_KEYSCAN;
EVENTTYPE EVENT_TIMER;
EVENTTYPE EVENT_LCD;

PROC key_scan()
{
	int x = 1;
    printf("key scan\n");
	return DEFAULT;
}


PROC lcd_drvin(void)
{
	int y = 4;
    printf("key scan\n");    
	return DEFAULT;
}


void main(void)
{
	proc_bind(EVENT_KEYSCAN,key_scan);//事件与响应函数绑定
	proc_bind(EVENT_LCD,lcd_drvin);
    event_bind(EVENT_KEYSCAN, 0); // 事件绑定到事件0
    event_bind(EVENT_LCD, 1); // 事件绑定到事件0    
// for( ;; ){
		get_proc(EVENT_KEYSCAN)(); //执行回调
		get_proc(EVENT_TIMER)();
		get_proc(EVENT_LCD)();
// }
}

