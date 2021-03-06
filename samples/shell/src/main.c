/*
 * Copyright (c) 2015 Intel Corporation
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

#include <zephyr.h>
#include <misc/printk.h>
#include <misc/shell.h>
#define DEVICE_NAME "test shell"

/*
 * Since we don't have kConfig in application level, we have the define here as
 * an example to what is needed to be in the relevant module kConfig file
 */
#define CONFIG_SAMPLE_MODULE_USE_SHELL


static int shell_cmd_ping(int argc, char *argv[])
{
	printk("pong\n");

	return 0;
}

static int shell_cmd_params(int argc, char *argv[])
{
	printk("argc = %d, argv[0] = %s\n", argc, argv[0]);

	return 0;
}

static int shell_cmd_uptime(int argc, char *argv[])
{
	printk("uptime: %u ms\n", k_uptime_get_32());

	return 0;
}

static int shell_cmd_cycles(int argc, char *argv[])
{
	printk("cycles: %u hw cycles\n", k_cycle_get_32());

	return 0;
}


#ifdef CONFIG_SAMPLE_MODULE_USE_SHELL

#define MY_SHELL_MODULE "sample_module"

static struct shell_cmd commands[] = {
	{ "ping", shell_cmd_ping },
	{ "uptime", shell_cmd_uptime },
	{ "cycles", shell_cmd_cycles },
	{ "params", shell_cmd_params, "print argc" },
	{ NULL, NULL }
};

#endif


void main(void)
{
#ifdef CONFIG_SAMPLE_MODULE_USE_SHELL
	SHELL_REGISTER(MY_SHELL_MODULE, commands);
#endif
}
