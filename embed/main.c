#include "ch.h"
#include "hal.h"
#include "test.h"

#include "src/cli.h"

/*
 * Red LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
	(void)arg;

	chRegSetThreadName("blinker");
	while (true) {
		palClearLine(LINE_LED_GREEN);
		chThdSleepMilliseconds(500);
		palSetLine(LINE_LED_GREEN);
		chThdSleepMilliseconds(500);
	}
}

/*
 * Application entry point.
 */
int main(void) {

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	cliEnable();

	/*
	 * Creates the blinker thread.
	 */
	// chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

	/*
	 * Normal main() thread activity, in this demo it does nothing except
	 * sleeping in a loop and check the button state.
	 */
	while (true) {
		chThdSleepMilliseconds(500);
	}
}
