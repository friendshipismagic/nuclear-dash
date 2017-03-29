#ifndef _CLI_H
#define _CLI_H

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "shell.h"
#include "chprintf.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
#define TEST_WA_SIZE    THD_WORKING_AREA_SIZE(256)

extern const ShellConfig shell_cfg1;

void cliEnable(void);

#endif
