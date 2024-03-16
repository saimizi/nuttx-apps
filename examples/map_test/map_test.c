/****************************************************************************
 * apps/examples/map_test/map_test.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * map test main
 ****************************************************************************/

// 64K page
#define FLASH_TO_PAGE(a) (a >> 16)
unsigned int cache_flash_mmu_set(int cpu_no, int pid, unsigned int vaddr,
				 unsigned int paddr, int psize, int num);

//#define DATA_PTR (0x3F500000)
#define INST_PTR (0x40400000)

#ifdef DATA_PTR
void print_ptr(unsigned char *ptr)
{
	int i;

	for (i = 0; i < 256; i++) {
		printf("0x%x, ", *(ptr++));
	}
	printf("\n");
}
#endif

#ifdef INST_PTR
void print_inst_ptr(unsigned int *ptr)
{
	int i;

	for (i = 0; i < 64; i++) {
		printf("0x%x\n", *(ptr + i));
	}
	printf("\n");
}
#endif

int main(int argc, FAR char *argv[])
{
	printf("Start mapping!!\n");
	int ret = 0;

#ifdef DATA_PTR
	ret = cache_flash_mmu_set(0, 1, DATA_PTR, 0x110000, 64, 1);
#endif

#ifdef INST_PTR
	ret = cache_flash_mmu_set(0, 1, INST_PTR, 0x110000, 64, 1);
#endif

	printf("End mapping!!\n");
	switch (ret) {
	case 0:
		printf("map success\n");
#ifdef DATA_PTR
		print_ptr((unsigned char *)DATA_PTR);
#endif
#ifdef INST_PTR
		print_inst_ptr((unsigned int *)INST_PTR);
#endif
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

	return 0;
}
