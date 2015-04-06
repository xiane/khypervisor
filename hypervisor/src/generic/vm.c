#include <vm.h>

vmid_t get_vmid() {
	return 0;
}
vmid_t create_vm() {
	return 1;
}
vm_state_t delete_vm(vmid_t vmid) {
	return UNDEFINED;
}
vm_state_t start_vm(vmid_t vmid) {
	return SCHEDULING;
}
vm_state_t shutdown_vm(vmid_t vmid) {
	return DEFINED;
}
