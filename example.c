#include <stdio.h>
#include "eframe.h"

efPROC(key_scan)
{
	int x = 1;
    printf("key scan\n");
}

efPROC(lcd_drvin)
{
    int y = 4;
    printf("lcd scan\n");     
}

efPROC(wake_esp8266)
{
  printf("esp8266 has been waked\n");  
}

u8 test() {
  u8 i = 0;
  u8 j = 1;
  u8 x;
  return x = i == 1 ? 1 : i;
}

void main(void)
{
  ef_setevent(EVENT_KEYSCAN, 1);
  ef_setevent(EVENT_TIMER, 2);
  ef_setevent(EVENT_LCD, 3);
  ef_setevent(EVENT_WAKE, 4);
  
  ef_bindhandler(EVENT_KEYSCAN,key_scan);//事件与响应函数绑定
  ef_bindhandler(EVENT_LCD,lcd_drvin);
  ef_bindhandler(EVENT_WAKE,wake_esp8266);

  ef_handle_event(EVENT_KEYSCAN); //根据事件执行处理回调
  ef_handle_event(EVENT_TIMER);
  ef_handle_event(EVENT_LCD);
  ef_handle_event(EVENT_WAKE);
  ef_idle();
  ef_event_add(1);
  printf("%d\n", test());
/* while(1) {
    ef_schedule_run();
    }*/
}
/* 
void main(void)
{
    event_bind(EVENT_KEYSCAN, 1); // 事件绑定到事件0
    event_bind(EVENT_LCD, 2); // 事件绑定到事件0
    event_bind(EVENT_WAKE, 3); // 事件绑定到事件0          
    proc_bind(EVENT_KEYSCAN,key_scan);//事件与响应函数绑定
    proc_bind(EVENT_LCD,lcd_drvin);
    proc_bind(EVENT_WAKE,wake_esp8266);    
 
//        event_proc(EVENT_KEYSCAN); //根据事件执行处理回调
//        event_proc(EVENT_TIMER);
//        event_proc(EVENT_LCD);
//        event_proc(EVENT_WAKE);

    ef_event_queue.add(EVENT_KEYSCAN); // 添加到队列
    ef_event_queue.add(EVENT_TIMER);
    ef_event_queue.add(EVENT_LCD);
    ef_event_queue.add(EVENT_WAKE);
        for( ;; ){
          ef_schedule_run();
        }
}
// snippet schedule
ERR ef_post(EVENTTYPE e) // 延迟处理
{
    return ef_event_queue.add(EVENT_TIMER); // 注意queue.add应该是原子操作  
}
ERR ef_signal(EVENTTYPE e) // 插入队头,优先处理
{
  return ef_event_queue.insert_head(EVENT_TIMER); // 注意queue.add应该是原子操作 
}

EVENTTYPE ef_event_occur_flag[MAX_PROC_AMOUNT] = {0};
void ef_schedule_run(void)
{
  int e = 0;
  while(!(event = event_queue.poll())) {
    event_proc(e);
  }
  ef_idle(); // 事件处理完进入空闲状态,休眠它
}
*/
