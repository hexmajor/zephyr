/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @brief ISR table for static ISR declarations for ARM
 *
 * Software ISR table for ARM
 */

#define _ASMLANGUAGE

#include <toolchain.h>
#include <sections.h>
#include <arch/cpu.h>

_ASM_FILE_PROLOGUE

/*
 * enable preprocessor features, such
 * as %expr - evaluate the expression and use it as a string
 */
.altmacro

/*
 * Define an ISR table entry
 * Define symbol as weak and give the section .gnu.linkonce
 * prefix. This allows linker overload the symbol and the
 * whole section by the one defined by a device driver
 */
.macro _isr_table_entry_declare index
	WDATA(_isr_irq\index)
	.section .gnu.linkonce.isr_irq\index
	_isr_irq\index: .word 0xABAD1DEA, _irq_spurious
.endm

/*
 * Declare the ISR table
 */
.macro _isr_table_declare from, to
	counter = \from
	.rept (\to - \from + 1)
		_isr_table_entry_declare %counter
		counter = counter + 1
	.endr
.endm

GTEXT(_irq_spurious)
GDATA(_sw_isr_table)

.section .isr_irq0
.align
_sw_isr_table:

_isr_table_declare 0 CONFIG_NUM_IRQS

