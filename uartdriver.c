#include "uartdriver.h"
static unsigned char ef_buf[UARTBUF_LEN] = {0};
static int _idx = -1;
event_t EVENT_UART_EF = 1;

/* 缓冲区满后会重复覆盖数据, 很对嵌入式个函数应该在串口中断中 */
void ef_tofaceuart(const u8 b)
{
  static u8 flag = 0;
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
