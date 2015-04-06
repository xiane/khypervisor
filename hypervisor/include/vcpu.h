#ifndef __VCPU_H__
#define __VCPU_H__

#include <armv7_regs.h>

/* Define vcpu state */
typedef enum vcpu_state {
	RUNNING,
	PAUSED
} __vcpu_state;

/* Define vcpu_arch */
typedef struct __vcpu_arch {
	__core_regs core_regs;
	__banked_regs banked_regs;
	__cp_regs cp_regs;
	__vcpu_state vcpu_state;

} vcpu;


typedef struct __virq_arch {
	/* virq to pirq */
	/* irq handler */
	unsigned int irq_map;
} vgic;

void init_vcpu(vcpu *vcpu);
void save_vcpu(vcpu *vcpu);
void restore_vcpu(vcpu *vcpu);

void init_virq(vgic *virq);
void save_virq(vgic *virq);
void restore_virq(vgic *virq);

#endif /* __VCPU_H__ */
