/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_io.h>
#include <sbi/sbi_console.h>
#include <sbi_utils/serial/inspiresemi-uart.h>
#include <uart_defs.h>

// Helper functions
#define _REG64(p, i) (*(volatile uint64_t *)((p) + (i)))
#define _REG32(p, i) (*(volatile uint32_t *)((p) + (i)))
#define _REG16(p, i) (*(volatile uint16_t *)((p) + (i)))
#define _REG8(p, i)  (*(volatile uint8_t *)((p) + (i)))

static void * uartregaddr;

void hondo_uart_putc(char c) 
{

  // Check for TX FIFO busy...
  //FIXME: LSR_THRE is set when FIFO is EMPTY!
  //    - changed to wait for empty on every char - would prefer to exploit fifo 
    //  - find the real 'full' bit if any.  Or write 8-16 chars after checking empty.

  while(!(_REG8(uartregaddr, UART_REG_LSR) & SERIAL_LSR_THRE));

  // Not busy send the char
  _REG8(uartregaddr, UART_REG_THR) = c;

}

int hondo_uart_getc( void ) 
{
	uint8_t ch;

  	// Check for a char, if none waiting return -1.  This is what OpenSBI expects.
  	uint8_t status = _REG8(uartregaddr, UART_REG_LSR);
  	if (status & SERIAL_LSR_DR)
  	{
		// Grab the character from the fifo.
  		ch = _REG8(uartregaddr, UART_REG_RHR);
  		return (uint32_t)(ch) & 0x000000ff;
  	}

	return -1;
}

// Turn this on for simulator baud rate
#define SIM 1

// init the uart to 8N1 and 115200 baud rate
int hondo_uart_init(void *uartctrl) {

  	uint8_t  databits, parity, stopbits, dll, dlm;

	uartregaddr = uartctrl;

#ifdef SIM
  	uint32_t uartdiv=0x02;  // Set to 1041000 for Simulation
#else
  	unsigned long long uart_target_baud = 115200ULL; // Baud Rate
  	const uint32_t clk_mhz = 33333333; // Input Clock 33.333Mhz
 	// Calculate the Divisor based on 33Mhz Input clock
  	uint32_t uartdiv = clk_mhz/(uart_target_baud * 16);
#endif

  	// Set the DLAB bit so we can program the baud rate
  	_REG8(uartctrl, UART_REG_LCR) |= SERIAL_LCR_DLAB;

  	/* Convert the divisor value into upper and lower */
  	dll = uartdiv & 0xff;
  	dlm = (uartdiv >> 8) & 0xff;

  	_REG8(uartctrl, UART_REG_DLL) = dll;
  	_REG8(uartctrl, UART_REG_DLM) = dlm;

  	// Unset the DLAB bit
  	_REG8(uartctrl, UART_REG_LCR) &= ~SERIAL_LCR_DLAB;

	databits = SERIAL_LCR_DATA8;
	parity = SERIAL_LCR_PARITYNONE;
	stopbits = SERIAL_LCR_STOP1;

	// Clear any interrupts at this time, we will poll for data...
	_REG8(uartctrl, UART_REG_IER) = 0x00;

	// Setup the fifo to 14 and clear rx and tx fifos
	_REG8(uartctrl, UART_REG_FCR) = SERIAL_FCR_RCVR_RESET | SERIAL_FCR_TXMT_RESET | SERIAL_FCR_RCVFIFO_14;

	// Clear out the DLAB bit and program the rest...
	_REG8(uartctrl, UART_REG_LCR) = (databits | parity | stopbits);

	// We are now all ready and can tx/rx data.. 

	return 0;
}