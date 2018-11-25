#include <stdio.h>
#include "eframe.h"


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
    printf("lcd scan\n");    
	return DEFAULT;
}


void main(void)
{
    event_bind(EVENT_KEYSCAN, 1); // 事件绑定到事件0
    event_bind(EVENT_LCD, 2); // 事件绑定到事件0      
	proc_bind(EVENT_KEYSCAN,key_scan);//事件与响应函数绑定
	proc_bind(EVENT_LCD,lcd_drvin);
// for( ;; ){
		event_proc(EVENT_KEYSCAN); //执行回调
		event_proc(EVENT_TIMER);
		event_proc(EVENT_LCD);
// }
}

