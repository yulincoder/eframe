# E-Frame
## TODO:
 - [X] 事件绑定到内置预定义事件 
 - [ ] 事件随时绑定,删除
 - [X] 事件处理过程绑定到对应事件 
 - [ ] 事件队列与基于队列调度 
 - [ ] 队列为空时的空闲函数,即进入睡眠 
 - [ ] 事件过程处理完的通知,即event_done数组支持(关于支持这一点,还需仔细思考这种情况发生的真正原因,参考TinyOS done事件设计)

### API List:
> 提供`event_t` 和`err_t` 两种类型,其中`err_t`的值为`SUCCESS`和`FAIL`

> `efPROC(handler) {}` 定义事件handler函数

> `ef_event_init()` 初始化事件变量, 如: `event_t KEY = ef_event_init();` 定义KEY事件,并初始化

> `ef_bindhandler(event, handler)` 绑定事件与handler

> `ef_post(event)` 提交事件

> `ef_scheduler_run()` 执行scheduler, 调用绑定的handler,处理提交的事件

> `ef_idle()` 没有事件发生时执行的函数. 这里应该调用平台相关睡眠函数

### Example:
```C
xxx_it.c file
-----------------------------------
// 外部中断函数
external interrupt function()
{
    ef_post(KEY); 提交事件
}

main.c file
-----------------------------------
//定义事件处理函数,
efPROC(key_handler) {
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

### 移植说明
移植需要修改以下几处:
1. eframe.h: #define MAX_HANDLER_AMOUNT n, n表示最大支持的事件数量, 该值不能大于2^8
2. eframe.h: #define MAX_QUEUE n, n表示未处理事件队列的长度, 队列满后新事件将提交失败
3. eframe.h: #define ef_idle() ... , 添加空闲任务, 一般添加处理器睡眠函数
4. eframe.h: #define atomic(s) ... , 在开头行添加屏蔽中断函数, 结尾行取消屏蔽中断函数
5. eframe.c: efPROC(ef_handle_null){}, 该函数为事件没有绑定对应处理函数时默认调用的函数, 可以根据情况添加内容或者不添加内容
