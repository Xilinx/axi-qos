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

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <uio_common.h>
#include <uio_axiqos.h>
#include <uio_axiqos_hw.h>

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define MIN_QOS_VAL 0
#define MAX_QOS_VAL 0xF

static uio_info uQosInfo;

int XAxiQos_SetRdQos(const uio_handle *InstancePtr, u32 Port, u32 Val) {
	/*
	 * Assert the arguments.
	 */
	if ((Val < MIN_QOS_VAL || Val > MAX_QOS_VAL) ||
					(Port < HPC0_PORT || Port > ALL_PORTS)) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Set Qos Value
	 */
	if (Port == ALL_PORTS) {
		for (Port = 0; Port < ALL_PORTS; Port++)
			XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_RD_QOS_OFFSET, Val);
	} else {
		XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_RD_QOS_OFFSET, Val);
	}
	return XST_SUCCESS;
}

int XAxiQos_GetRdQos(const uio_handle *InstancePtr, u32 Port) {
	u32 Val;
	/*
	 * Assert the arguments.
	 */
	if (Port < HPC0_PORT || Port > ALL_PORTS) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Get Qos Value
	 */
	if (Port == ALL_PORTS) {
		for (Port = 0; Port < ALL_PORTS; Port++) {
			Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_RD_QOS_OFFSET);
			printf("RD QOS of port %d is %d\n", Port, Val);
		}
	} else {
		Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_RD_QOS_OFFSET);
		printf("RD QOS of port %d is %d\n", Port, Val);
	}
	return XST_SUCCESS;
}

int XAxiQos_SetWrQos(const uio_handle *InstancePtr, u32 Port, u32 Val) {
	/*
	 * Assert the arguments.
	 */
	if ((Val < MIN_QOS_VAL || Val > MAX_QOS_VAL) ||
					(Port < HPC0_PORT || Port > ALL_PORTS))	{
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Set Qos Value
	 */
	if (Port == ALL_PORTS) {
		for (Port = 0; Port < ALL_PORTS; Port++)
			XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_WR_QOS_OFFSET, Val);
	} else {
		XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_WR_QOS_OFFSET, Val);
	}
	return XST_SUCCESS;
}

int XAxiQos_GetWrQos(const uio_handle *InstancePtr, u32 Port) {
	u32 Val;
	/*
	 * Assert the arguments.
	 */
	if (Port < HPC0_PORT || Port > ALL_PORTS) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Get Qos Value
	 */
	if (Port == ALL_PORTS) {
		for (Port = 0; Port < ALL_PORTS; Port++) {
			Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_WR_QOS_OFFSET);
			printf("WR QOS of port %d is %d\n", Port, Val);
		}
	} else {
		Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_WR_QOS_OFFSET);
		printf("WR QOS of port %d is %d\n", Port, Val);
	}
	return XST_SUCCESS;
}

int XAxiQos_SetRdIssue(const uio_handle *InstancePtr, u32 Port, u32 Val) {
	/*
	 * Assert the arguments.
	 */
	if ((Val < MIN_QOS_VAL || Val > MAX_QOS_VAL) ||
					(Port < HPC0_PORT || Port > ALL_PORTS)) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Set Qos Value
	 */
	if (Port == ALL_PORTS) {
		for (Port = 0; Port < ALL_PORTS; Port++)
			XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_RD_ISSUE_OFFSET, Val);
	} else {
		XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_RD_ISSUE_OFFSET, Val);
	}
	return XST_SUCCESS;
}

int XAxiQos_GetRdIssue(const uio_handle *InstancePtr, u32 Port) {
	u32 Val;
	/*
	 * Assert the arguments.
	 */
	if (Port < HPC0_PORT || Port > ALL_PORTS) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Get Qos Value
	 */
	if (Port == ALL_PORTS) {
		for (Port = 0; Port < ALL_PORTS; Port++) {
			Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_RD_ISSUE_OFFSET);
			printf("RD Issue of port %d is %d\n", Port, Val);
		}
	} else {
		Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_RD_ISSUE_OFFSET);
		printf("RD Issue of port %d is %d\n", Port, Val);
	}
	return XST_SUCCESS;
}

int XAxiQos_SetWrIssue(const uio_handle *InstancePtr, u32 Port, u32 Val) {
	/*
	 * Assert the arguments.
	 */
	if ((Val < MIN_QOS_VAL || Val > MAX_QOS_VAL) ||
					(Port < HPC0_PORT || Port > ALL_PORTS)) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Set Qos Value
	 */
	if (Port == ALL_PORTS) {
		for (Port = 0; Port < ALL_PORTS; Port++)
			XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_WR_ISSUE_OFFSET, Val);
	} else {
		XAxiQos_WriteReg(InstancePtr->Control_bus_BaseAddress + (Port * HPPORT_BASE_OFFSET),
			HPPORT_WR_ISSUE_OFFSET, Val);
	}
	return XST_SUCCESS;
}

int XAxiQos_GetWrIssue(const uio_handle *InstancePtr, u32 Port) {
	u32 Val;
	/*
	 * Assert the arguments.
	 */
	if (Port < HPC0_PORT || Port > ALL_PORTS) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Get Qos Value
	 */
	if (Port == ALL_PORTS) {
		for (Port = 0; Port < ALL_PORTS; Port++) {
			Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_WR_ISSUE_OFFSET);
			printf("WR Issue val of port %d is %d\n", Port, Val);
		}
	} else {
		Val = XAxiQos_ReadReg(InstancePtr->Control_bus_BaseAddress +
					(Port * HPPORT_BASE_OFFSET), HPPORT_WR_ISSUE_OFFSET);
		printf("WR Issue val of port %d is %d\n", Port, Val);
	}
	return XST_SUCCESS;
}

int uAxiQos_Init(uio_handle *qos_handle) {

	int ret = uio_Initialize(&uQosInfo, QOS_INSTANCE_NAME);
	if (ret == XST_DEVICE_NOT_FOUND)
		return ret;

	assert(uQosInfo.isInitialized == XIL_COMPONENT_IS_READY);
	ret = uio_get_Handler(&uQosInfo, qos_handle, MAP_CNT);
	if (ret != XST_SUCCESS)
		return ret;
	assert(qos_handle->IsReady == XIL_COMPONENT_IS_READY);
	return ret;
}

int uAxiQos_DeInit(uio_handle *qos_handle) {

	int ret;

	assert(qos_handle->IsReady == XIL_COMPONENT_IS_READY);
	ret = uio_release_handle(&uQosInfo, qos_handle, MAP_CNT);
	if (ret != XST_SUCCESS)
		return ret;
	ret = uio_Release(&uQosInfo);
	if (ret != XST_SUCCESS)
			return ret;

	return ret;
}



