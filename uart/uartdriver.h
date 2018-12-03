#include <string.h>
#include "../eframe.h"
#ifndef __UARTDRIVER_H__
#define __UARTDRIVER_H__

#define UARTBUF_LEN 20 // 缓冲区长度
extern void ef_tofaceuart(const char);
extern void ef_uart_flush(void);
extern void ef_uart_recv(char *);
extern ef_event_t EVENT_UART_EF; // 串口事件
#endif


