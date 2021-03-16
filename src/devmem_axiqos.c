/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <devmem_axiqos.h>

#define MIN_QOS_VAL 0
#define MAX_QOS_VAL 0xF

#define AXI_QOS_CTRL_BASE       0xFD360000
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

int XAxiQos_SetQos(const mem_info *InstancePtr, u32 qos_type, u32 Val) {

	if (InstancePtr == NULL) {
		printf("%s Null instance pointer passed\n", __func__);
		return FAIL;
	}

	if (InstancePtr->IsReady != XIL_COMPONENT_IS_READY) {
		printf("Instance mapping not ready");
		return FAIL;
	}

	if (Val < MIN_QOS_VAL || Val > MAX_QOS_VAL)
		return FAIL;
	/*
	 * Set Qos Value
	 */
	switch(qos_type) {
		case RD_QOS:
			XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress,
										 HPPORT_RD_QOS_OFFSET, Val);
			break;

		case WR_QOS:
			XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress,
										 HPPORT_WR_QOS_OFFSET, Val);
			break;

		case RD_ISSUE:
			XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress,
										 HPPORT_RD_ISSUE_OFFSET, Val);
			break;

		case WR_ISSUE:
			XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress,
										 HPPORT_WR_ISSUE_OFFSET, Val);
			break;
		default:
			printf("Invalid QOS TYPE\n");
	}
	return SUCCESS;
}

int XAxiQos_GetQos(const mem_info *InstancePtr, u32 qos_type) {
	u32 Val;

	if (InstancePtr == NULL) {
		printf("%s Null pointer passed\n", __func__);
		return FAIL;
	}
	if (InstancePtr->IsReady != XIL_COMPONENT_IS_READY) {
		printf("Instance mapping not ready");
		return FAIL;
	}

	if (Val < MIN_QOS_VAL || Val > MAX_QOS_VAL)
		return FAIL;

	/*
	 * Get Qos Value
	 */
	switch(qos_type) {
		case RD_QOS:
			Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress,
											 HPPORT_RD_QOS_OFFSET);
			break;

		case WR_QOS:
			Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress,
											 HPPORT_WR_QOS_OFFSET);
			break;

		case RD_ISSUE:
			Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress,
											 HPPORT_RD_ISSUE_OFFSET);
			break;

		case WR_ISSUE:
			Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress,
											 HPPORT_WR_ISSUE_OFFSET);
			break;
		default:
			printf("Invalid QOS TYPE\n");
		}

	return Val;
}

int XAxiQos_Init(mem_info *InstancePtr, unsigned int port_num) {

	InstancePtr->memfd = open("/dev/mem", O_RDWR | O_SYNC);

    if (InstancePtr->memfd == -1) {
		printf("Can't open /dev/mem.\n");
		return FAIL;
	}

	InstancePtr->Control_bus_BaseAddress =
						mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE,
						MAP_SHARED, InstancePtr->memfd,
						(AXI_QOS_CTRL_BASE + port_num * 0x10000) &
						 ~MAP_MASK);

	if (InstancePtr->Control_bus_BaseAddress == (void *) -1) {
		close(InstancePtr->memfd);
		printf("Can't map the memory to user space.\n");
		return FAIL;
	}

	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

	return 0;
}

int XAxiQos_DeInit(mem_info *InstancePtr) {

	if (InstancePtr->IsReady)
	{
		if (munmap(InstancePtr->Control_bus_BaseAddress, MAP_SIZE) == -1) {
			printf("Can't unmap memory from user space.\n");
			return FAIL;
		}

		close(InstancePtr->memfd);
		InstancePtr->Control_bus_BaseAddress = NULL;
		InstancePtr->IsReady = XIL_COMPONENT_NOT_READY;
	}
}
