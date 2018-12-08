/*
 * Copyright (c) 2018 Google LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __EFRAME_H__
#define  __EFRAME_H__

// setting below items to port different platform.

// this value should be defined greater than 10
// , and the 1-10 are allocated to the default events in eframe.
#include <stdio.h>		// For PC
#define efMAX_HANDLER_AMOUNT 20
/**
 * default events in eframe in the range of 1-10:
 *  > event <nil>: booted
 *             The same as main function. The first event posted by the MCU when it starts.
 *             User need to declare the `efPROC(main_handler){ ... }` to process the main event.
 *  > event 1: efEVENT_SCH
 *             That sync post the event will tigger the schudler of eframe.  
 *  > event 2: ...
 */
  
#define efMAX_QUEUE_LEN 10 // 
#define efENTER_ATOMIC  printf("enter atomic regeion\n")
#define efEXIT_ATOMIC   printf("exit atomic regeion\n")


/****** eframe *******/
typedef unsigned int ef_u16;
typedef unsigned char ef_u8;
typedef ef_u8 ef_event_t;
typedef enum {
  efSUCCESS = 0,
  efFAIL 
} ef_err_t;

#define efPROC(event) void event(void) // a intuitive way to declare a handler
typedef void (*ef_handler_t) (void); // handler type
 

// The real length of events is efMAX_QUEUE_LEN + 1
// , as the head-node is a guard node that do not take a value.
#define efREAL_LEN efMAX_QUEUE_LEN + 1	// Real length of event queue.
    
// event 0 is null event, presenting no events.
#define efEVENT_NULL 0
#define efEVENT_SCH 1 // default event, to launch the scheduler
#define booted main
#define main_handler main


extern ef_event_t ef_event_cnt;

// assign a unique ID to a event variable for initialzation.
#define ef_event_init() ef_event_cnt++ 
    
/* 响应函数返回的状态码 */ 
#define efDEFAULT 0		//默认状态码（无意义）
#define efNO_PROC 1		//没有响应函数
    
/* handler list, the indexs are IDs of events binded */ 
extern ef_handler_t ef_handler_list[efMAX_HANDLER_AMOUNT];
  
/* bind a handler to specified event */ 
#define ef_bindhandler(ef_event, ef_handler) \
do {\
 ef_handler_list[ef_event] = ef_handler;\
} while (0)
 
extern efPROC(ef_handle_null);	// a event without handler, this handler is going to execute.

/*  handle the event through involving handler binded the event */
#define ef_handle_event(event)\
do {\
 switch(event) {\
 case 1:ef_scheduler_run();\
 default:(ef_handler_list[event] ? ef_handler_list[event] : ef_handle_null) (); \
}} while (0)

// post a synchronization event.
// Execute handler immediately upon invocation.
// Synchronization event have the highest priority.
#define ef_syncpost(event) ef_handle_event(event)

// extern void ef_idle(void);

// a convenient way to implement atomic operation. 
#define ef_atomic(s) \
do {\
 efENTER_ATOMIC;\
 s \
 efEXIT_ATOMIC;\
} while (0)

extern ef_err_t ef_post(ef_event_t e);
extern void ef_scheduler_run(void);

#endif // __TFRAME_H__


