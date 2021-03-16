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

#ifndef AXI_QOS_H_
#define AXI_QOS_H_

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdint.h>

#define QOS_INSTANCE_NAME	"axi_qos"
#define MAP_CNT             0x1
#define XAxiQos_ReadReg(addr,off) 	*((volatile uint32_t *) ( ((uint8_t*)addr) + off ))
#define XAxiQos_WriteReg(addr, off, val) 	*((volatile uint32_t *) ( ((uint8_t*)addr)+ off )) = (val)

#define AXI_QOS_CTRL_BASE       0xFD360000
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define SUCCESS		0
#define FAIL		-1

#define XIL_COMPONENT_IS_READY  1
#define XIL_COMPONENT_NOT_READY 0

/************************** Constant Definitions ****************************/
#define HPPORT_BASE_OFFSET          0x10000
#define HPPORT_RDCTRL_OFFSET        0x0
#define HPPORT_RD_ISSUE_OFFSET      0x4
#define HPPORT_RD_QOS_OFFSET        0x8
#define HPPORT_WRCTRL_OFFSET        0x14
#define HPPORT_WR_ISSUE_OFFSET      0x18
#define HPPORT_WR_QOS_OFFSET        0x1C
#define HPPORT_CTRL_OFFSET          0xF04
#define HPPORT_SAFETY_CHECK_OFFSET      0xF0C


#define HPPORT_INTR_STS 0xE00

/**************************** Type Definitions ******************************/
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short int u16;

typedef struct {
    int isInitialized;
    int IsReady;
    int memfd;
    void *Control_bus_BaseAddress;
} mem_info;

enum Qos_Type {
	RD_QOS = 1,
	WR_QOS,
	RD_ISSUE,
	WR_ISSUE,
};

enum AxiQos_Port {
	HPC0_PORT,
	HPC1_PORT,
	HP0_PORT,
	HP1_PORT,
	HP2_PORT,
	HP3_PORT,
	ALL_PORTS,
};

int XAxiQos_Init(mem_info *InstancePtr, u32 port_num);
int XAxiQos_DeInit(mem_info *InstancePtr);
int XAxiQos_SetQos(const mem_info *InstancePtr, u32 qos_type, u32 Val);
int XAxiQos_GetQos(const mem_info *InstancePtr, u32 qos_type);
int XAxiQos_SetWrQos(mem_info *InstancePtr, u32 Val);
int XAxiQos_GetWrQos(mem_info *InstancePtr);
int XAxiQos_SetRdIssue(mem_info *InstancePtr, u32 Val);
int XAxiQos_GetRdIssue(mem_info *InstancePtr);
int XAxiQos_SetWrIssue(mem_info *InstancePtr, u32 Val);
int XAxiQos_GetWrIssue(mem_info *InstancePtr);
#endif /* UAFIFM_QOS_H_ */
