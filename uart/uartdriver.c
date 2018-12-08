/*
 * Copyright (c) 2019 SenseAge LLC. ZhangT
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

#include "uartdriver.h"
static unsigned char ef_buf[UARTBUF_LEN] = {0};
static int _idx = -1;
ef_event_t EVENT_UART_EF = 9;

/* 缓冲区满后会重复覆盖数据, 很对嵌入式个函数应该在串口中断中 */
void ef_tofaceuart(const char b)
{
  static char flag = 0;
  if(b == '$') {
    flag = 0;
    if( ++_idx >= UARTBUF_LEN - 1) {
      _idx = UARTBUF_LEN - 1;
    }    
    ef_buf[_idx] = '\0';
    ef_post(EVENT_UART_EF); // post uart event;
    return;
  }

  if(b == '%'){
    flag = 1;
    if(_idx > 0) _idx--; // 取代缓冲区中原来的'\0',拼接到新接收的字符
    return;
  }
  if(flag) {
    if( ++_idx >= UARTBUF_LEN - 1) {
      _idx = UARTBUF_LEN - 1;
    }
    if(_idx < UARTBUF_LEN - 1) {
      ef_buf[_idx] = b;
    } else {
      ef_buf[_idx] = '\0';
    }
  }
}

void ef_uart_flush(void)
{
  _idx = -1;
}

/* TODO: 添加选择串口号参数 */
void ef_uart_recv(char *dest)
{
  strcpy(dest, ef_buf);
}
