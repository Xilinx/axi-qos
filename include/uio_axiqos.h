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

#ifndef UAXI_QOS_H_
#define UAXI_QOS_H_

#include "uio_common.h"

#define QOS_INSTANCE_NAME	"axi_qos"
#define MAP_CNT             0x1
#define XAxiQos_ReadReg 	HW_READ
#define XAxiQos_WriteReg 	HW_WRITE

#define EXIT_SUCCESS	0
#define EXIT_FAIL		1

enum AxiQos_Port {
	HPC0_PORT,
	HPC1_PORT,
	HP0_PORT,
	HP1_PORT,
	HP2_PORT,
	HP3_PORT,
	ALL_PORTS,
};

int uAxiQos_Init(uio_handle *qos_handle);
int uAxiQos_DeInit(uio_handle *qos_handle);
int XAxiQos_SetRdQos(const uio_handle *InstancePtr, u32 Port, u32 Val);
int XAxiQos_GetRdQos(const uio_handle *InstancePtr, u32 Port);
int XAxiQos_SetWrQos(const uio_handle *InstancePtr, u32 Port, u32 Val);
int XAxiQos_GetWrQos(const uio_handle *InstancePtr, u32 Port);
int XAxiQos_SetRdIssue(const uio_handle *InstancePtr, u32 Port, u32 Val);
int XAxiQos_GetRdIssue(const uio_handle *InstancePtr, u32 Port);
int XAxiQos_SetWrIssue(const uio_handle *InstancePtr, u32 Port, u32 Val);
int XAxiQos_GetWrIssue(const uio_handle *InstancePtr, u32 Port);
#endif /* UAFIFM_QOS_H_ */
