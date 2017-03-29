# Is ChibiOS present?
CHIBI_HERE = $(shell if [ -d "ChibiOS" ]; then echo yes; fi)
ifeq ($(CHIBI_HERE),yes)
	include Makefile.chibios
endif

# Downloads ChibiOS
# Change to true to download ugfx
UGFX = false
install:
	@if [ -d "ChibiOS" ]; then \
		cd ChibiOS; git pull; \
	else \
		git clone https://github.com/ChibiOS/ChibiOS.git; \
		cd ChibiOS; git checkout stable_16.1.x; \
	fi
	@if [ "$(UGFX)" = "true" ] || [ -d ugfx ]; then \
		if [ -d ugfx ]; then \
			cd ugfx; git pull; \
		else \
			git clone https://git.ugfx.io/ugfx/ugfx.git ugfx; \
		fi; \
	fi

# Starts OpenOCD
OCD_DIR = /usr/share/openocd/scripts
OCD_BOARD = board.cfg
openocd:
	openocd -f $(OCD_DIR)/board/$(OCD_BOARD).cfg

# Lauches GDB and flashes the target
debug: $(BUILDDIR)/$(PROJECT).elf
	$(TRGT)gdb $(BUILDDIR)/$(PROJECT).elf

# Programs the board
program:
	cp build/*.bin /Volumes/NODE_L476RG

# Fires up a serial terminal to listen to the serial port
SERIAL_TERM = minicom
SERIAL_DEVICE = .usbmodem1423
serial:
	sudo $(SERIAL_TERM) -D /dev/tty$(SERIAL_DEVICE)

.PHONY: install openocd debug serial

