/* Copyright (c) 2020 InspireSemi Inc. */

#ifndef _CRYPTO_UART_H
#define _CRYPTO_UART_H

/* Register offsets */
#define UART_REG_DLL            0x00
#define UART_REG_DLM            0x01

#define UART_REG_RHR            0x00
#define UART_REG_THR            0x00
#define UART_REG_IER            0x01
#define UART_REG_ISR            0x02
#define UART_REG_FCR            0x02
#define UART_REG_LCR            0x03
#define UART_REG_MCR            0x04
#define UART_REG_LSR            0x05
#define UART_REG_MSR            0x06



/* IER mask */
#define SERIAL_IER_RCVEN         0x01   /* receive interrupt enable    */
#define SERIAL_IER_THREN         0x01   /* transmitter holding reg empty enable    */
#define SERIAL_IER_RLSEN         0x01   /* receiver line status enable    */
#define SERIAL_IER_RMSEN         0x01   /* receive modem status enable    */

/* FCR control */
#define SERIAL_FCR_ENABLE        0x01   /* enable FIFO's               */
#define SERIAL_FCR_RCVR_RESET    0x02   /* reset receiver FIFO         */
#define SERIAL_FCR_TXMT_RESET    0x04   /* reset transmit FIFO         */
#define SERIAL_FCR_RCVFIFO_1     0x00   /* receive FIFO threshold 1    */
#define SERIAL_FCR_RCVFIFO_4     0x40   /* receive FIFO threshold 4    */
#define SERIAL_FCR_RCVFIFO_8     0x80   /* receive FIFO threshold 8    */
#define SERIAL_FCR_RCVFIFO_14    0xc0   /* receive FIFO threshold 14   */

/* LCR control */
#define SERIAL_LCR_DATA5         0x00   /* 5-bit character             */
#define SERIAL_LCR DATA6         0x01   /* 6-bit character             */
#define SERIAL_LCR_DATA7         0x02   /* 7-bit character             */
#define SERIAL_LCR_DATA8         0x03   /* 8-bit character             */
#define SERIAL_LCR_DATA_MSK      0x03   /* MASK for data field         */

#define SERIAL_LCR_STOP1         0x00   /* 1 stop bit                  */
#define SERIAL_LCR_STOP15        0x04   /* 1.5 stop bit, if data is 5-bit */
#define SERIAL_LCR_STOP2         0x04   /* 2 stop bit                  */
#define SERIAL_LCR_STOP_MSK      0x04   /* MASK for stop bit field     */

#define SERIAL_LCR_PARITYNONE    0x00   /* No parity                   */
#define SERIAL_LCR_PARITYODD     0x08   /* Odd parity                  */
#define SERIAL_LCR_PARITYEVEN    0x18   /* Even parity                 */
#define SERIAL_LCR_PARITYMARK    0x28   /* Mark parity                 */
#define SERIAL_LCR_PARITYSPACE   0x38   /* Space parity                */
#define SERIAL_LCR_PARITY_MASK   0x38   /* MASK for parity field       */

#define SERIAL_LCR_BREAK         0x40   /* request to send a 'break'   */
#define SERIAL_LCR_DLAB          0x80   /* enable divisor latch registers */

/* MCR control */
#define SERIAL_MCR_DTR           0x01   /* Data Terminal Ready         */
#define SERIAL_MCR_RTS           0x02   /* Request To Send             */
#define SERIAL_MCR_OUT1          0x04   /* General purpose output      */
#define SERIAL_MCR_OUT2          0x08   /* General purpose output      */
#define EXAR_INT_ENABLE			 0x08   /* This is the interrupt enable MCR[3] for EXAR UART */

#define SERIAL_MCR_LOOP          0x10   /* Local loop back             */
#define SERIAL_MCR_AFE           0x20   /* Auto-flow control enable    */

/* LSR status */
#define SERIAL_LSR_DR            0x01   /* Character ready             */
#define SERIAL_LSR_OE            0x02   /* RX-ERROR: Overrun           */
#define SERIAL_LSR_PE            0x04   /* RX-ERROR: Parity            */
#define SERIAL_LSR_FE            0x08   /* RX-ERROR: Framing (stop bit) */
#define SERIAL_LSR_BI            0x10   /* 'BREAK' detected            */
#define SERIAL_LSR_THRE          0x20   /* Transmit Holding empty      */
#define SERIAL_LSR_TEMT          0x40   /* Transmitter empty (IDLE)    */
#define SERIAL_LSR_FIFOERR       0x80   /* RX-ERROR: FIFO              */

/* MSR status */
#define SERIAL_MSR_DCTS          0x01   /* Delta clear to send         */
#define SERIAL_MSR_DDSR          0x02   /* Delta data set ready        */
#define SERIAL_MSR_TERI          0x04   /* Trailing edge ring ind.     */
#define SERIAL_MSR_DDCD          0x08   /* Delta data carrier detect   */
#define SERIAL_MSR_CTS           0x10   /* Clear to send               */
#define SERIAL_MSR_DSR           0x20   /* Data Set Ready              */
#define SERIAL_MSR_RI            0x40   /* Ring Indicator              */
#define SERIAL_MSR_DCD           0x80   /* Data carrier detect         */


/* TXCTRL register */
#define UART_TXEN               0x1
#define UART_TXNSTOP            0x2
#define UART_TXWM(x)            (((x) & 0xffff) << 16)

/* RXCTRL register */
#define UART_RXEN               0x1
#define UART_RXWM(x)            (((x) & 0xffff) << 16)

/* IP register */
#define UART_IP_TXWM            0x1
#define UART_IP_RXWM            0x2


#ifndef __ASSEMBLER__

/* compat function for debug output, implemented in main.c */
//int puts(const char *s);

#include <stdint.h>
#endif /* !__ASSEMBLER__ */

#endif /* _CRYPTO_UART_H */
