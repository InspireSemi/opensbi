#
# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (c) 2019 Western Digital Corporation or its affiliates.
#
# Authors:
#   Atish Patra <atish.patra@wdc.com>
#

# Compiler flags
platform-cppflags-y =
platform-cflags-y =
platform-asflags-y =
platform-ldflags-y =

# Blobs to build
FW_TEXT_START=0x88020000000000

FW_PAYLOAD=y

# This needs to be 2MB aligned for 64-bit system
FW_PAYLOAD_OFFSET=0x030000

#FW_PAYLOAD_FDT_ADDR=0xB3C018000000

R64IMA=0

ifeq ($(R64IMA), 1)
PLATFORM_RISCV_XLEN = 64
PLATFORM_RISCV_ABI = lp64
PLATFORM_RISCV_ISA = rv64ima 
PLATFORM_RISCV_CODE_MODEL = medany
else
PLATFORM_RISCV_XLEN = 64
PLATFORM_RISCV_ABI = lp64d
PLATFORM_RISCV_ISA = rv64imafdc
PLATFORM_RISCV_CODE_MODEL = medany
endif