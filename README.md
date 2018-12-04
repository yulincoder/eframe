![eFrame](https://user-images.githubusercontent.com/10429180/49326426-1bc6b000-f58d-11e8-81a1-a65ba931b1a9.jpg)

eframe is an event-driven programming framework for low power applications using 8-bit or 16 MCU

[中文](https://github.com/yulincoder/eframe/blob/master/ZHREADME.md


### TODO:
 - [X] handler dynamic binding
 - [ ] Supports the `handle_done` event (maybe refer to the TinyOS)
 - [X] Supports synchronous events by `ef_syncpost()`, which can preempt common events. 
#### Whether reasonable?
 - [ ] The enevt is deivered to the specified handler at runtime.
 - [ ] Events should carray some data.

### API List:
> Two type in eframe, `ef_event_t` 和`ef_err_t`

> `efPROC(handler) {}` Implementation of a handler

> `ef_event_init()` Initizlizing a variable such as define a KEY event`event_t KEY = ef_event_init();`

> `ef_bindhandler(event, handler)` binding a handler to a event

> `ef_post(event)` post a event to the queue.

> `ef_syncpost(event)` post a synchronization event, which is going to be processed immediately.

> `ef_idle()` idle handler

### Serial port API:
> `void ef_tofaceuart(const u8 b)` place the function to the interrupt of usart.

> `void ef_uart_recv(char *buf)` read the data in underlying buffer to `buf`.

> `void ef_uart_flush(void)` flush the underlying buffer.


### Default events in eframe: (Default events does not require binding by `ef_bindhandler()`)
1. `booted` The same as main function. The first event posted by the MCU when it starts.
2. `efEVENT_SCH`: That synchronously post the event will tigger the schudler of eframe.  

### Example: 
##### 1. External interrpt example 
```C 
xxx_it.c file
-----------------------------------
#include "eframe.h"
// external interrupt 
external interrupt function()
{
    ef_post(KEY); // post a KEY event to queue.
}

main.c file
-----------------------------------
#include "eframe.h"
// Define the handler in order to process KEY event
efPROC(key_handler)
{
    printf("The KEY1 is pressed.\n");
}

efPROC(booted) // define the handler related `booted` 
{
    event_t KEY = ef_event_init(); // allocate a unique ID to event.
    ef_bindhandler(KEY, key_handler); //bind the key handler to KEY event.

    ef_syncpost(efEVENT_SCH); // tigger the schudler of eframe.
}
```
##### 2. Serial example 
```C
uart_it.c file
-----------------------------------
#include "uartdriver.h"
uart interrupt function()
{
  ...
  ef_tofaceuart(BUFF); 
  ...
}

main.c file
-----------------------------------
efPROC(uart_handler)
{
  static char buf[20] = {0};
  ef_uart_recv(buf); // read the data from usart buffer
  ef_uart_flush(); // flush it
  puts(buf); //
}

efPROC(booted)
{
  ef_bindhandler(EVENT_UART_EF, uart_handler); 
  ef_syncpost(efEVENT_SCH);
}
```

2018.12.2 v0.1
