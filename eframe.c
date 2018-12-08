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

/**
 * Author: Zhang T <paradoxt@qq.com> 
 */

#include "eframe.h"

/* Regeister handler of event into this list   */
ef_handler_t ef_handler_list[efMAX_HANDLER_AMOUNT] = {0}; 
ef_event_t ef_event_cnt = 10; // 1-10为框架内置事件,用户事件从11开始


// When an event has no binded to any handler by coder, this handler is given it.
efPROC(ef_handle_null)
{
	// do something to handle the event without handler
}

// queue of pending events 
ef_event_t ef_eventqueue[efREAL_LEN] = { 0 };	
static ef_event_t _tail = 0;
static ef_event_t _head = 0;

#define ef_queue_size() (_tail >= _head ? _tail - _head: efREAL_LEN - _head + _tail)
ef_err_t ef_queue_add(const ef_event_t e)
{
	ef_u8 temp_tail = _tail + 1 == efREAL_LEN ? 0 : _tail + 1;
	if (ef_queue_size() == efREAL_LEN - 1) {
		return efFAIL;
	}
	ef_eventqueue[_tail = temp_tail] = e;
	return efSUCCESS;
}

ef_event_t ef_queue_poll()
{
	ef_u8 temp_head = _head + 1 == efREAL_LEN ? 0 : _head + 1;
	if (!ef_queue_size()) {
		return efEVENT_NULL;
	}
	return ef_eventqueue[_head = temp_head];
}

// post event to queue
ef_err_t ef_post(const ef_event_t e)
{
	ef_err_t err = efSUCCESS;
	ef_atomic(
		err = ef_queue_add(e);
	      );
	return err;
}

efPROC(ef_scheduler_run)
{
	ef_event_t e = efEVENT_NULL;
    // for( ;; ) {
      while ((e = ef_queue_poll()) != efEVENT_NULL) {
          ef_handle_event(e);
      }
    // }
	// ef_idle();
}

