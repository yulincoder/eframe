![eFrame](https://user-images.githubusercontent.com/10429180/49326426-1bc6b000-f58d-11e8-81a1-a65ba931b1a9.jpg)
### TODO:
 - [X] 事件初始化 
 - [ ] 事件随时绑定,删除
 - [X] 事件处理过程绑定到对应事件 
 - [X] 事件队列与基于队列调度 
 - [X] 队列为空时的空闲函数,即进入睡眠 
 - [ ] 事件过程处理完的通知,即event_done数组支持(关于支持这一点,还需仔细思考这种情况发生的真正原因,参考TinyOS done事件设计)
 - [X] 同步事件ef_syncpost() 抢占
#### 是否要实现的功能?
 - [ ] 事件动态投递到指定handler
 - [ ] 事件是否携带数据

### API List:
> 提供`event_t` 和`err_t` 两种类型,其中`err_t`的值为`SUCCESS`和`FAIL`

> `efPROC(handler) {}` 定义事件handler函数

> `ef_event_init()` 初始化事件变量, 如: `event_t KEY = ef_event_init();` 定义KEY事件,并初始化

> `ef_bindhandler(event, handler)` 绑定事件与handler

> `ef_post(event)` 提交事件

> `ef_scheduler_run()` 执行scheduler, 调用绑定的handler,处理提交的事件

> `ef_idle()` 没有事件发生时执行的函数. 这里应该调用平台相关睡眠函数

### 串口驱动API:
> `void ef_tofaceuart(const u8 b)` 作为从串口硬件接收数据

> `void ef_uart_recv(char *buf)` 将串口接收到的数据存入buf

> `void ef_uart_flush(void)` 清空底层接收缓存区


### 系统默认事件:
1. uartdriver.h: `EVENT_UART_EF` 事件1. 当串口接收到`"%hellor$"`时, 可以触发该事件,并可以从`ef_uart_recv(buf)`函数读到字符串`"hello"`


### Example: 
##### 1. 外部中断按钮example 
```C 
xxx_it.c file
-----------------------------------
#include "eframe.h"
// 外部中断函数
external interrupt function()
{
    ef_post(KEY); //提交事件
}

main.c file
-----------------------------------
#include "eframe.h"
//定义事件处理函数,
efPROC(key_handler)
{
    printf("The KEY1 is pressed.\n");
}

void main(void)
{
    event_t KEY = ef_event_init(); //定义并初始化一个事件
    ef_bindhandler(KEY, key_handler); //绑定按键事件与按键处理函数

    while(1) {
        ef_scheduler_run(); //执行处理事件,没有事件发生则执行idle函数
    }
}
```
##### 2. 串口中断example 
```C
uart_it.c file
-----------------------------------
#include "uartdriver.h"
uart interrupt function()
{
  ...
  ef_tofaceuart(BUFF); //当收到一个完整的% $组合时, 该函数内会提交EVENT_UART_EF事件
  ...
}

main.c file
-----------------------------------
efPROC(uart_handler)
{
  static char buf[20] = {0};
  ef_uart_recv(buf); // read the date from buffer
  ef_uart_flush(); // flush the underly buffer
  puts(buf); //
}

void main(void)
{
  ef_bindhandler(EVENT_UART_EF, uart_handler); //绑定串口事件与处理函数, 该事件为内置事件,不需要定义

  while(1) {
    // 如果收到 %hello$, 则可以看到将会输出 hello
    ef_scheduler_run();
  }
}
```

### 移植说明
移植需要修改以下几处:
1. eframe.h: #define MAX_HANDLER_AMOUNT n, n表示最大支持的事件数量, 该值不能大于2^8, 且不能小于11, 系统默认占用1-10事件
2. eframe.h: #define MAX_QUEUE n, n表示未处理事件队列的长度, 队列满后新事件将提交失败
3. eframe.c: void ef_idle() { } , 添加空闲任务, 一般添加处理器睡眠函数
4. eframe.h: #define atomic(s) ... , 在开头行添加屏蔽中断函数, 结尾行取消屏蔽中断函数
5. eframe.c: efPROC(ef_handle_null){}, 该函数为事件没有绑定对应处理函数时默认调用的函数, 可以根据情况添加内容或者不添加内容
6. 移植串口接收驱动: 在串口中断内调用void ef_tofaceuart(const u8 b)函数, 并将硬件缓冲区内的数据作为该函数参数. 使用该驱动接收数据需要包含在符号%$内,如%hello$, 可接收到字符串hello,并触发事件EVENT_UART_EF

2018.12.2 v0.1
