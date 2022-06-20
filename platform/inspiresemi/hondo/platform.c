/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Changes Copyright (c) 2020 InspireSemi Inc.
 * 
 * Authors:
 *   Atish Patra <atish.patra@wdc.com>
 *   Marc Karasek <mkarasek@inspiresemi.com>
 */

#include <libfdt.h>
#include <sbi/riscv_asm.h>
#include <sbi/riscv_io.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_platform.h>
#include <sbi_utils/fdt/fdt_fixup.h>
#include <sbi_utils/irqchip/plic.h>
#include <sbi_utils/serial/inspiresemi-uart.h>
#include <sbi_utils/sys/clint.h>

/* clang-format off */

/* Full tlb flush always */
#define HONDO_TLB_RANGE_FLUSH_LIMIT		0

#define HONDO_HART_COUNT			1 //   Only 1 for Sim
#define HONDO_HART_STACK_SIZE		0x8000

#define HONDO_SYS_CLK				1000000000

//#define HONDO_CLINT_ADDR			0x2000000

//#define HONDO_PLIC_ADDR				0xc000000
//#define HONDO_PLIC_NUM_SOURCES			0x35
//#define HONDO_PLIC_NUM_PRIORITIES		7

#define UART0_CTRL_ADDR _AC(0x2EE00000,UL)
#define UART0_CTRL_SIZE _AC(0x10,UL)
//#define UART1_CTRL_ADDR _AC(0x10011000,UL)
//#define UART1_CTRL_SIZE _AC(0x1000,UL)
#define UART_CTRL_ADDR UART0_CTRL_ADDR
#define UART_CTRL_SIZE UART0_CTRL_SIZE
#define UART_REG(offset) UART0_REG(offset)
#define UART0_REG(offset) _REG8(UART0_CTRL_ADDR, offset)

/* clang-format on */

#if 0
static struct plic_data plic = {
	.addr = HONDO_PLIC_ADDR,
	.num_src = HONDO_PLIC_NUM_SOURCES,
};

static struct clint_data clint = {
	.addr = HONDO_CLINT_ADDR,
	.first_hartid = 0,
	.hart_count = HONDO_HART_COUNT,
	.has_64bit_mmio = TRUE,
};
#endif

static void hondo_modify_dt(void *fdt)
{

}

static int hondo_final_init(bool cold_boot)
{
	void *fdt;

	if (!cold_boot)
		return 0;

	fdt = sbi_scratch_thishart_arg1_ptr();
	hondo_modify_dt(fdt);

	return 0;
}

static int hondo_console_init(void)
{
	return hondo_uart_init ((void *)UART0_CTRL_ADDR);
}

static u64 hondo_get_tlbr_flush_limit(void)
{
	return HONDO_TLB_RANGE_FLUSH_LIMIT;
}

static u32 hondo_hart_index2id[HONDO_HART_COUNT] = {
	[0] = 0x1dd2,  // Need to find out our ID
};

static int hondo_system_reset(u32 type)
{
	/* For now nothing to do. */
	return 0;
}

const struct sbi_platform_operations platform_ops = {
	.final_init			= hondo_final_init,
	.console_putc		= hondo_uart_putc,
	.console_getc		= hondo_uart_getc,
	.console_init		= hondo_console_init,
	.get_tlbr_flush_limit	= hondo_get_tlbr_flush_limit,
	.system_reset		= hondo_system_reset
};

const struct sbi_platform platform = {
	.opensbi_version	= OPENSBI_VERSION,
	.platform_version	= SBI_PLATFORM_VERSION(0x0, 0x01),
	.name			= "InspireSemi Hondo",
	.features		= SBI_PLATFORM_DEFAULT_FEATURES,
	.hart_count		= (HONDO_HART_COUNT),
	.hart_index2id		= hondo_hart_index2id,
	.hart_stack_size	= SBI_PLATFORM_DEFAULT_HART_STACK_SIZE,
	.platform_ops_addr	= (unsigned long)&platform_ops
};
