#ifndef __VMEM_H__
#define __VMEM_H__

typedef struct __vmem_arch {
	unsigned int vtcr;
	unsigned int vttbr;
	unsigned int memory_start;
	unsigned int memory_offset;
} vmem;

void init_vmem(vmem *vmem);
void save_vmem(vmem *vmem);
void restore_vmem(vmem *vmem);

#endif /* __VMEM_H__ */
