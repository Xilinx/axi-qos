/*
 * Copyright 2021 Xilinx Inc.
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

#ifndef AXIQOS_HW_H_
#define AXIQOS_HW_H_

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions ****************************/
#define HPPORT_BASE_OFFSET			0x10000
#define HPPORT_RDCTRL_OFFSET		0x0
#define HPPORT_RD_ISSUE_OFFSET		0x4
#define HPPORT_RD_QOS_OFFSET		0x8
#define HPPORT_WRCTRL_OFFSET		0x14
#define HPPORT_WR_ISSUE_OFFSET		0x18
#define HPPORT_WR_QOS_OFFSET		0x1C
#define HPPORT_CTRL_OFFSET			0xF04
#define HPPORT_SAFETY_CHECK_OFFSET		0xF0C


#define HPPORT_INTR_STS 0xE00

#ifdef __cplusplus
}
#endif
#endif /* AXIQOS_HW_H_ */
