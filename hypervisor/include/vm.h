#ifndef __VIRTUAL_MACHINE_H__
#define __VIRTUAL_MACHINE_H__

#include <vcpu.h>
#include <vmem.h>
#include <virq.h>

typedef unsigned char vmid_t;

typedef enum __vm_state {
	UNDEFINED,
	DEFINED,
	SCHEDULING,
} vm_state_t;

typedef struct virtual_machine {
	vmid_t vmid; /* vmid is from 0 to 255 */

	vcpu *vcpu;
	vmem *vmem;
	vgic *virq;

	vm_state_t state;
} vm;

vmid_t get_vmid();
vmid_t create_vm();
vm_state_t delete_vm(vmid_t vmid);
vm_state_t start_vm(vmid_t vmid);
vm_state_t shutdown_vm(vmid_t vmid);

#endif /* __VIRTUAL_MACHINE_H__ */
