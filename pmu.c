// This file contains some helpers to enable/disbale the and interact with the
// ARM Cortex R4 PMU. See http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0363e/CHDCBAAH.html
// for more information.

// If you want to use this code with Nexmon, uncomment the following part
/***********
#pragma NEXMON targetregion "patch"

#include <wrapper.h> // wrapper definitions for functions that already exist in the firmware
#include <structs.h> // structures that are used by the code in the firmware
#include <helper.h>  // useful helper functions
#include <patcher.h> // macros used to craete patches such as BLPatch, BPatch, ...
***********/

#include "pmu.h"

// Enable performance monitoring by cleaning all registers and chosing counters
// The PMU has three registers, which can count different things.
// See http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0363e/CHDCBAAH.html
// which counters are available and which value has to be used.
__attribute__((naked))
void
enable_performance_monitor(void)
{
	asm(
		"mov r0, #0\n"
		"mcr p15, #0, r0, c9, c12, #5\n"	// Select performance monitor counter #0
		"mov r0, #0x01\n"					// Number instruction cache miss (0x01)
		"mcr p15, #0, r0, c9, c13, #1\n"	// Write 1 to EVTSELx Register

		"mov r0, #1\n"
		"mcr p15, #0, r0, c9, c12, #5\n"	// Select performance monitor counter #1
		"mov r0, #0x03\n"					// Numebr data cache misses (0x03)
		"mcr p15, #0, r0, c9, c13, #1\n"	// Write 1 to EVTSELx Register

		"mov r0, #2\n"
		"mcr p15, #0, r0, c9, c12, #5\n"	// Select performance monitor counter #2"
		"mov r0, #0x08\n"					// Instructions architecturally executed (0x08)
		"mcr p15, #0, r0, c9, c13, #1\n"	// Write 1 to EVTSELx Register

		"mrc p15, #0, r0, c9, c12, #0\n"	// Read PMNC Register
		"orr r0, r0, #7\n"					// Reset cycle and performance counters and enable
		"mcr p15, #0, r0, c9, c12, #0\n"	// Write 0 to PMNC Register
		"bx  lr\n"
	);
}

// Enable the PMU
__attribute__((naked))
void
performance_monitor_start(void)
{
	asm (
		"mcr p15, #0, r0, c9, c12, #1\n"	// Write 1 to CNTENS Register to enable
		"BX LR\n"
	);
}

// Disable the PMU
__attribute__((naked))
void
performance_monitor_stop(void)
{
	asm(
    	"mcr p15, #0, r0, c9, c12, #2\n"	// Write 2 to CNTENC Register" to disable
  		"bx  lr\n"
	);
}

// Get the value from the first performance register
__attribute__((naked))
unsigned int
performance_monitor_read_counter_0(void)
{
	asm(
		"mov r0, #0\n"
		"mcr p15, #0, r0, c9, c12, #5\n"	// Select performance monitor counter #0
		"mrc p15, #0, r0, c9, c13, #2\n"	// Read current PMNx Register
		"bx lr\n"
	);
}

// Get the value from the second performance register
__attribute__((naked))
unsigned int
performance_monitor_read_counter_1(void)
{
	asm(
		"mov r0, #1\n"
		"mcr p15, #0, r0, c9, c12, #5\n"	// Select performance monitor counter #1
		"mrc p15, #0, r0, c9, c13, #2\n"	// Read current PMNx Register
		"bx lr\n"
	);
}

// Get the value from the third performance register
__attribute__((naked))
unsigned int
performance_monitor_read_counter_2(void)
{
	asm(
		"mov r0, #2\n"
		"mcr p15, #0, r0, c9, c12, #5\n"	// Select performance monitor counter #2
		"mrc p15, #0, r0, c9, c13, #2\n"	// Read current PMNx Register
		"bx  lr\n"
	);
}

// Get the value from cycle count register
__attribute__((naked))
unsigned int
performance_monitor_read_cycle_count(void)
{
	asm(
		"mrc p15, #0, r0, c9, c13, #0\n"	// Read CCNT Register
		"bx lr\n"
	);
}
