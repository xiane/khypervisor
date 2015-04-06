#ifndef __VIRTUAL_MACHINE_H__
#define __VIRTUAL_MACHINE_H__

typedef enum virtual_machine_state {
	UNDEFINED,
	DEFINED,
} vm_state;

typedef struct virtual_machine {
	unsigned char vmid; /* vmid is from 0 to 255 */

	vcpu *vcpu;
	vmem *vmem;
	virq *virq;

	vm_state state;
} vm;

unsigned char get_vmid();

unsigned char create_vm();
void delete_vm(unsigned char vmid);
void start_vm(unsigned char vmid);

#endif /* __VIRTUAL_MACHINE_H__ */
