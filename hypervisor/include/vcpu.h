#ifndef __VCPU_H__
#define __VCPU_H__

#include <armv7_regs.h>

typedef struct __vcpu_arch {
	__core_regs core_regs;
	__banked_regs banked_regs;
	__cp_regs cp_regs;
} vcpu;

void init_vcpu(vcpu *v);
void save_vcpu(vcpu *v);
void restore_vcpu(vcpu *v);

#endif /* __VCPU_H__ */
