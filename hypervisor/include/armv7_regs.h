#ifndef __ARMV7_REGS_H__
#define __ARMV7_REGS_H__

/* Define ARMv7 core registers */
typedef struct armv7_core_registers {
	unsigned int r0;
	unsigned int r1;
	unsigned int r2;
	unsigned int r3;
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int r12;
	unsigned int sp; /* r13 */
	unsigned int lr; /* r14 */
	unsigned int pc; /* r15 */
	unsigned int cpsr;
} __core_regs;

/* Define ARMv7 banked registers */
typedef struct armv7_banked_registers {
	unsigned int sp_usr;	/* ??? */
	unsigned int lr_usr;	/* ??? */

	unsigned int sp_svc;
	unsigned int lr_svc;
	unsigned int spsr_svc;

	unsigned int sp_abt;
	unsigned int lr_abt;
	unsigned int spsr_abt;

	unsigned int sp_und;
	unsigned int lr_und;
	unsigned int spsr_und;

	unsigned int sp_irq;
	unsigned int lr_irq;
	unsigned int spsr_irq;

	unsigned int r8_fiq;
	unsigned int r9_fiq;
	unsigned int r10_fiq;
	unsigned int r11_fiq;
	unsigned int r12_fiq;
	unsigned int sp_fiq; // r13
	unsigned int lr_fiq; // r14
	unsigned int spsr_fiq;
} __banked_regs;

/* Define ARMv7 coprocessor's registers */
typedef struct armv7_coprocessor_registers {
    unsigned int vbar;
    unsigned int ttbr0;
    unsigned int ttbr1;
    unsigned int ttbcr;
    unsigned int sctlr;
} __cp_regs;

#endif /*__ARMV7_REGS_H__ */
