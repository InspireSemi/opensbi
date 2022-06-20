/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SERIAL_SIFIVE_UART_H__
#define __SERIAL_SIFIVE_UART_H__

#include <sbi/sbi_types.h>

void hondo_uart_putc(char ch);

int hondo_uart_getc(void);

int hondo_uart_init(void *uartctrl);

#endif
