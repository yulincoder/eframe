#include <stdio.h>
#include "eframe.h"

efPROC(key_scan)
{
	static int x = 1;
    printf("\tkey scan: %d\n", x++ );
}

efPROC(lcd_drvin)
{
	static int x = 1;    
    printf("\tlcd scan: %d\n", x++ );     
}

efPROC(wake_esp8266)
{
  static int x = 1;      
  printf("\tesp8266 has been waked: %d\n", x++ );  
}

efPROC(timer)
{
  static int x = 1;      
  printf("\tesp8266 has been waked: %d\n", x++ );  
}



void main(void)
{
  event_t EVENT_KEYSCAN = ef_event_init();
  event_t EVENT_TIMER = ef_event_init();
  event_t EVENT_LCD = ef_event_init();
  event_t EVENT_WAKE = ef_event_init();
  printf("%d, %d, %d, %d\n", EVENT_KEYSCAN, EVENT_TIMER, EVENT_LCD, EVENT_WAKE);
  
  ef_bindhandler(EVENT_KEYSCAN,key_scan);//事件与响应函数绑定
  ef_bindhandler(EVENT_LCD,lcd_drvin);
  ef_bindhandler(EVENT_WAKE,wake_esp8266);
  ef_bindhandler(EVENT_TIMER,timer);  

  ef_post(EVENT_KEYSCAN); // 提交事件
  ef_post(EVENT_TIMER);
  ef_post(EVENT_WAKE);
  ef_post(EVENT_LCD);
  ef_post(EVENT_KEYSCAN);
  ef_post(EVENT_TIMER);
  ef_post(EVENT_WAKE);
  ef_post(EVENT_LCD); 
  ef_post(EVENT_KEYSCAN);
  ef_post(EVENT_TIMER);
  ef_post(EVENT_WAKE);
  ef_post(EVENT_LCD); 
  ef_schedule_run(); // 运行事件处理
  
  ef_post(EVENT_KEYSCAN);
  ef_post(EVENT_TIMER);
  ef_post(EVENT_WAKE);
  ef_post(EVENT_LCD);
  ef_schedule_run();  
}

