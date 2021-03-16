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

#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <devmem_axiqos.h>
#define DEFAULT_PORTNUM			(0x6)

/* setting to default values */
int set_qos = -1;
int qos_type = -1;
u32 qos_val = 0xf;

const char port_name[7][5] = {
				"HPC0",
				"HPC1",
				"HP0",
				"HP1",
				"HP2",
				"HP3"
				};

const char qos_name[6][9] = {
				"\0",
				"RDQoS",
				"WRQoS",
				"RDISSUE",
				"WRISSUE",
				};

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
	{"set qos value :range[0-0xf] \n",
		required_argument, NULL, 's'},
	{"get qos value for the given port \n",
		required_argument, NULL, 'g'},
	{"qos type :range[1-4] \n1-read qos\n2-write qos\n"
		"3-outstanding_rdissue\n4-outstanding_wrissue\n",
		required_argument, NULL, 't'},
	{"port no\n 0-HPC0\n 1-HPC1\n 2-HP0\n 3-HP1\n 4-HP2\n"
		" 5-HP3\n 6-All ports\n",
		required_argument, NULL, 'p'},
	{"version\n", required_argument, NULL, 'v'},
	{"help\n", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

static int XAxiQos_rd_wr_qos(u32 set_qos, u32 metric,
								u32 port_num, u32 qos_val);

static void usage(const char *name)
{
	int i = 0;

	fprintf(stdout, "Xilinx copyright 2021\n\n");
	fprintf(stdout, "This application is to set QOS value"
								"for AXI ports\n on ZYNQMP platform\n\n");
	fprintf(stdout, "usage: %s [OPTIONS]\n\n", name);
	fprintf(stdout, "%s -s <val> -t <qos type> -p <port num> \n\n", name);
	fprintf(stdout, "%s -g -t <qos type> -p <port num> \n\n", name);

	for (i=0 ; i<(sizeof(long_opts)/sizeof(long_opts[0])) - 2; i++)
		fprintf(stdout, "-%c represents %s\n",
			long_opts[i].val, long_opts[i].name);
	i++;
}

int main(int argc, char *argv[])
{
	int cmd_opt;
	u32 port_num = 0xf;

	if (argc == 1) {
		usage(argv[0]);
		return 0;
	}

	while ((cmd_opt =
		getopt_long(argc, argv, "hgvc:s:t:p:", long_opts,
			    NULL)) != -1) {
		switch (cmd_opt) {
		case 0:
			/* long option */
			break;

		case 's':
			set_qos = 1;
			qos_val	= getopt_integer(optarg);
			if (qos_val < 0 || qos_val > 0xf) {
				printf("-s is to set qos value for the AXI ports\n"
						"select in the range of [0-0xf] \n");
				return 0;
			}
			break;

		case 'g':
			set_qos = 0;
			break;

		case 't':
			qos_type = getopt_integer(optarg);
			if (qos_type < 1 || qos_type > 4) {
				printf("-t is to selct the qos type for the AXI ports\n"
						"select in the range of [1-4] \n"
						"1-read qos\n2-write qos\n3-outstanding_rdissue\n"
						"4-outstanding_wrissue\n");
				return 0;
			}
			break;

		case 'p':
			port_num = getopt_integer(optarg);
			if (port_num < 0 || port_num > 0x7) {
				port_num = DEFAULT_PORTNUM;
				printf("-p: to select port no: 0-HPC0 \n1-HPC1 \n"
						"2-HP0 \n3-HP1 \n4-HP2 \n5-HP3 \n6-All ports\n");
				return 0;
			}
			break;

		case 'v':
			printf("Xilinx ZYNQMP axi qos app version 0.1 \n");
			return 0;
			break;

		case 'h':
			usage(argv[0]);
			return 0;
			break;
		default:
			printf("Invalid option. type -h for help \n");
			return 0;
		}
	}

	if (set_qos < 0 || qos_type < 0 || port_num < 0) {
		printf("Invalid input, type -h for help\n");
		printf("Usage: \n");
		printf("%s -s <val> -t <qos type> -p <port num> \n\n", argv[0]);
		printf("%s -g -t <qos type> -p <port num> \n\n", argv[0]);
		return 0;
	}

	if ( port_num >= 0 && port_num <= 5) {
		return XAxiQos_rd_wr_qos(set_qos, qos_type, port_num, qos_val);
	} else if (port_num == 6) {
		u32 port;
		for (port = 0; port < port_num; port++) {
			XAxiQos_rd_wr_qos(set_qos, qos_type, port, qos_val);
		}
	} else {
		printf("Invalid port number\n");
	}
}


static int XAxiQos_rd_wr_qos(u32 set_qos, u32 metric,
								 u32 port_num, u32 qos_val) {
	mem_info qos_handle;
	int ret;
	u32 Val;

	ret = XAxiQos_Init(&qos_handle, port_num);
	if (ret > 0)
		return ret;
	if (set_qos) {
		XAxiQos_SetQos(&qos_handle, metric, qos_val);
		printf ("%s value was set for %s port"
									" with 0x%x\n", qos_name[metric],
									port_name[port_num], qos_val);
	} else {
		Val = XAxiQos_GetQos(&qos_handle, metric);
		printf("%s value of %s port is 0x%x\n",qos_name[metric],
										 port_name[port_num], Val);
	}
	return XAxiQos_DeInit(&qos_handle);
}
