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
#define CR4864_TLB_RANGE_FLUSH_LIMIT		0

#define CR4864_HART_COUNT			1 //   Only 1 for Sim
#define CR4864_HART_STACK_SIZE		0x8000

#define CR4864_SYS_CLK				1000000000

//#define CR4864_CLINT_ADDR			0x2000000

//#define CR4864_PLIC_ADDR				0xc000000
//#define CR4864_PLIC_NUM_SOURCES			0x35
//#define CR4864_PLIC_NUM_PRIORITIES		7

#define UART0_CTRL_ADDR _AC(0x2F208700,UL)
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
	.addr = CR4864_PLIC_ADDR,
	.num_src = CR4864_PLIC_NUM_SOURCES,
};

static struct clint_data clint = {
	.addr = CR4864_CLINT_ADDR,
	.first_hartid = 0,
	.hart_count = CR4864_HART_COUNT,
	.has_64bit_mmio = TRUE,
};
#endif

static void cr4864_modify_dt(void *fdt)
{

}

static int cr4864_final_init(bool cold_boot)
{
	void *fdt;

	if (!cold_boot)
		return 0;

	fdt = sbi_scratch_thishart_arg1_ptr();
	cr4864_modify_dt(fdt);

	return 0;
}

static int cr4864_console_init(void)
{
	return cr4864_uart_init ((void *)UART0_CTRL_ADDR);
}

static u64 cr4864_get_tlbr_flush_limit(void)
{
	return CR4864_TLB_RANGE_FLUSH_LIMIT;
}

static u32 cr4864_hart_index2id[CR4864_HART_COUNT] = {
	[0] = 0x003F,
};

static void cr4864_system_reset(u32 type, u32 reason)
{
	/* For now nothing to do. */
	return;
}

const struct sbi_platform_operations platform_ops = {
	.final_init			= cr4864_final_init,
	.console_putc		= cr4864_uart_putc,
	.console_getc		= cr4864_uart_getc,
	.console_init		= cr4864_console_init,
	.get_tlbr_flush_limit	= cr4864_get_tlbr_flush_limit,
	.system_reset		= cr4864_system_reset
};

const struct sbi_platform platform = {
	.opensbi_version	= OPENSBI_VERSION,
	.platform_version	= SBI_PLATFORM_VERSION(0x0, 0x01),
	.name			= "InspireSemi Hondo",
	.features		= SBI_PLATFORM_DEFAULT_FEATURES,
	.hart_count		= (CR4864_HART_COUNT),
	.hart_index2id		= cr4864_hart_index2id,
	.hart_stack_size	= SBI_PLATFORM_DEFAULT_HART_STACK_SIZE,
	.platform_ops_addr	= (unsigned long)&platform_ops
};
