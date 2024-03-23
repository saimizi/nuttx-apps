#include <stdio.h>

#define ALIGN_64K_MASK (1 << 16)
#define ALIGN_MASK(x, mask) (((x) + (mask - 1)) & ~(mask - 1))

// 64K page
#define FLASH_TO_PAGE(a) (a >> 16)
unsigned int cache_flash_mmu_set(int cpu_no, int pid, unsigned int vaddr,
				 unsigned int paddr, int psize, int num);
void print_long_ptr(void *p)
{
	unsigned long *ptr = p;
	int i;

	for (i = 0; i < 64; i++) {
		printf("0x%lx\n", *(ptr + i));
	}
	printf("\n");
}

void print_byte_ptr(void *p)
{
	unsigned char *ptr = p;
	int i;

	for (i = 0; i < 256; i++) {
		printf("0x%x, ", *(ptr++));
	}
	printf("\n");
}

void *flash_map(unsigned long virt, unsigned long offset)
{
	unsigned long virt_align = ALIGN_MASK(virt, ALIGN_64K_MASK);
	unsigned long offset_align = ALIGN_MASK(offset, ALIGN_64K_MASK);

	if (virt_align != virt) {
		printf("virt: 0x%lx -> 0x%lx\n", virt, virt_align);
	}

	if (offset_align != offset) {
		printf("offset: 0x%lx -> 0x%lx\n", offset, offset_align);
	}

	int ret = cache_flash_mmu_set(0, 1, virt_align, offset_align, 64, 1);

	switch (ret) {
	case 0:
		printf("map success\n");
		break;
	case 1:
		printf("map failed: vaddr or paddr is not alligned\n");
		break;
	case 2:
		printf("pid error\n");
		break;
	case 3:
		printf("psize error\n");
		break;
	case 4:
		printf("mmu table to be written is out of range\n");
		break;
	case 5:
		printf("vaddr is out of range\n");
		break;
	default:
		printf("Impossible.\n");
		break;
	}

	if (!ret) {
		return (void *)virt_align;
	} else {
		return NULL;
	}
}
