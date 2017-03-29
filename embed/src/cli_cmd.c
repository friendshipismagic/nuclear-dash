#include "ch.h"
#include "hal.h"
#include "halconf.h"
#include "string.h"             // Looks like memcpy is in there ...
#include "chprintf.h"
#include "chstreams.h"

#include "cli_cmd.h"

uint32_t ato32(char *s) {
	uint32_t ret = 0;
	uint8_t sign = 1;

	if (*s == '-') sign = -1;
	do {
		ret = ret * 10 + *s - '0';

	} while (*(++s));

	return sign == 1 ? ret : -ret;
}

void cmd_test (BaseSequentialStream *chp, int argc, char *argv[]) {
	(void) argc;
	(void) argv;

	chprintf(chp, "Hello World!\r\n");
}

void cmd_toggle_leds(BaseSequentialStream *chp, int argc, char *argv[]) {
	(void) argc;
	(void) argv;

	palToggleLine(LINE_LED_GREEN);
}

void cmd_motor(BaseSequentialStream *chp, int argc, char *argv[]) {
	if (argc < 2) {
		chprintf(chp, "Missing value.\r\n");
	}

	// TODO
	int val = ato32(argv[1]);
}


