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

#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include "uio_axiqos.h"
#include "uio_common.h"


#define DEFAULT_SETQOS			(0x0)
#define DEFAULT_METRIC			(0x0)
#define DEFAULT_QOSVAL			(0x7)
#define DEFAULT_PORTNUM			(0x6)

u32 set_qos = DEFAULT_SETQOS;
u32 metric = DEFAULT_METRIC;
u32 qos_val = DEFAULT_QOSVAL;
u32 port_num = DEFAULT_PORTNUM;

static uint32_t getopt_integer(char *optarg)
{
  int rc;
  uint32_t value;
  rc = sscanf(optarg, "0x%x", &value);
  if (rc <= 0)
    rc = sscanf(optarg, "%ul", &value);
  return value;
}

static struct option const long_opts[] = {
	{"set qos value :range[0-1] \n0-get qos \n1-set qos\n",
		required_argument, NULL, 's'},
	{"Qos type :range[1-4] \n1-read qos\n2-write qos\n"
		"3-outstanding_rdissue\n4-outstanding_wrissue\n",
		required_argument, NULL, 'm'},
	{"port no\n 0-HPC0\n 1-HPC1\n 2-HP0\n 3-HP1\n 4-HP2\n"
		" 5-HP3\n 6-All ports\n",
		required_argument, NULL, 'p'},
	{"val :range[0-0xF]\n", required_argument, NULL, 'v'},
	{"help\n", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

static int XAxiQos_rd_wr_qos(u32 set_qos, u32 metric,
								u32 port_num, u32 qos_val);

static void usage(const char *name)
{
	int i = 0;

	fprintf(stdout, "%s\n\n", name);
	fprintf(stdout, "usage: %s [OPTIONS]\n\n", name);

	for (i=0 ; i<(sizeof(long_opts)/sizeof(long_opts[0])) - 2; i++)
		fprintf(stdout, "-%c represents %s\n",
			long_opts[i].val, long_opts[i].name);
	fprintf(stdout, "-%c (%s) print usage help and exit\n",
		long_opts[i].val, long_opts[i].name);
	i++;
}

int main(int argc, char *argv[])
{
	int cmd_opt;

	while ((cmd_opt =
		getopt_long(argc, argv, "hc:s:m:v:p:", long_opts,
			    NULL)) != -1) {
		switch (cmd_opt) {
		case 0:
			/* long option */
			break;

		case 's':
			set_qos	= getopt_integer(optarg);
			if (set_qos < 0 || set_qos > 1) {
				set_qos = DEFAULT_SETQOS;
				printf("-s is to set/get qos configuration for the AXI ports\n"
						"select in the range of [0-1] \n"
						"0-get qos\n1-set qos\n");
			}
			break;

		case 'm':
			metric = getopt_integer(optarg);
			if (metric < 1 || metric > 4) {
				metric = DEFAULT_METRIC;
				printf("-m is to selct the qos type for the AXI ports\n"
						"select in the range of [1-4] \n"
						"1-read qos\n2-write qos\n3-outstanding_rdissue\n"
						"4-outstanding_wrissue\n");
			}
			break;

		case 'p':
			port_num = getopt_integer(optarg);
			if (port_num < 0 || port_num > 0x7) {
				port_num = DEFAULT_PORTNUM;
				printf("-p: to select port no: 0-HPC0 \n1-HPC1 \n"
						"2-HP0 \n3-HP1 \n4-HP2 \n5-HP3 \n6-All ports\n");
			}
			break;

		case 'v':
			qos_val	= getopt_integer(optarg);
			if (qos_val < 0 || qos_val > 0xF) {
				qos_val = DEFAULT_QOSVAL;
				printf("-w qos value should be 0-0xF\n");
			}
			break;

		case 'h':
		default:
			usage(argv[0]);
			return 0;
			break;
		}
	}
	if (cmd_opt == 0) {
		usage(argv[0]);
		return 0;
	}
	return XAxiQos_rd_wr_qos(set_qos, metric, port_num, qos_val);
}


static int XAxiQos_rd_wr_qos(u32 set_qos, u32 metric,
								 u32 port_num, u32 qos_val) {
	uio_handle qos_handle;
	int ret;

	ret = uAxiQos_Init(&qos_handle);
	if (ret > 0)
		return ret;
	if (set_qos) {
		switch(metric) {
			case 1:
				XAxiQos_SetRdQos(&qos_handle, port_num, qos_val);
				break;
			case 2:
				XAxiQos_SetWrQos(&qos_handle, port_num, qos_val);
				break;
			case 3:
				XAxiQos_SetRdIssue(&qos_handle, port_num, qos_val);
				break;
			case 4:
				XAxiQos_SetWrIssue(&qos_handle, port_num, qos_val);
				break;
			default:
				break;
			}
	} else {
		switch(metric) {
			case 1:
				XAxiQos_GetRdQos(&qos_handle, port_num);
				break;
			case 2:
				XAxiQos_GetWrQos(&qos_handle, port_num);
				break;
			case 3:
				XAxiQos_GetRdIssue(&qos_handle, port_num);
				break;
			case 4:
				XAxiQos_GetWrIssue(&qos_handle, port_num);
				break;
			default:
				break;
		}
	}

	return uAxiQos_DeInit(&qos_handle);
}
