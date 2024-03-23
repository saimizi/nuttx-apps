/****************************************************************************
 * apps/examples/hello/hello_main.c
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

#define DATA_PTR (0x3F500000)
#define INST_PTR (0x40400000)

/****************************************************************************
 * Public Functions
 ****************************************************************************/
void *flash_map(unsigned long virt, unsigned long offset);
void print_long_ptr(void *p);
void print_byte_ptr(void *p);

/****************************************************************************
 * map_test Main
 ****************************************************************************/

int main(int argc, FAR char *argv[])
{
	void *virt = flash_map(DATA_PTR, 0x110000);
	if (virt) {
		print_byte_ptr(virt);
	}

	virt = flash_map(INST_PTR, 0x110000);
	if (virt) {
		print_long_ptr(virt);
	}

	return 0;
}
