#include "cli.h"

#include "cli_cmd.h"

static const ShellCommand commands[] = {
	{"test", cmd_test},
	{"toggle_leds", cmd_toggle_leds},
	{"motor", cmd_motor},
	{NULL, NULL}
};

const ShellConfig shell_cfg1 = {
	(BaseSequentialStream *)&SD2,
	commands
};

void cliEnable() {
	/**
	 * Init serial driver
	 */
	SerialConfig serialCfg = { 9600, 0 };
	sdStart(&SD2, &serialCfg);

	/*
	 * Shell manager initialization.
	 */
	shellInit();

	static thread_t *shelltp = NULL;
	shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);
}

