#ifndef _CLI_CMD_H
#define _CLI_CMD_H

void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_toggle_leds(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_motor(BaseSequentialStream *chp, int argc, char *argv[]);

#endif

