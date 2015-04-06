# Usage: make
# Example:
#	$ make	     	; build for bmguest
#	$ make LINUX=y	; build for linux guest

# Include config file
include config-default.mk
LIB_DIR=../lib
COMMON_LOADER_DIR=$(LIB_DIR)/loader
OBJS += boot.o main.o drivers/uart.o drivers/pl011.o drivers/timer.o\
	$(LIB_DIR)/print.o \
	$(LIB_DIR)/format.o \
	$(LIB_DIR)/string.o \
	$(LIB_DIR)/exception.o \
	$(LIB_DIR)/gic.o \
	$(LIB_DIR)/test_vtimer.o \
	$(COMMON_LOADER_DIR)/linuxloader.o \
	$(COMMON_LOADER_DIR)/guestloader_common.o \
	$(COMMON_LOADER_DIR)/cli.o \
	$(COMMON_LOADER_DIR)/monitor/monitor_cli.o \
	$(COMMON_LOADER_DIR)/monitor/guest_monitor.o
GUESTLOADERIMG	= guestloader.axf
GUESTLOADERBIN	= guestloader.bin
LD_SCRIPT	= model.lds.S
INCLUDES	= -I. -I$(LIB_DIR) \
			 -I$(COMMON_LOADER_DIR) \
			 -I$(COMMON_LOADER_DIR)/monitor

CPPFLAGS	+= $(INCLUDES)
CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
OBJCOPY	= $(CROSS_COMPILE)objcopy
GUESTLOADERCONFIGS = -DBM_GUEST
ifeq ($(LINUX), y)
GUESTLOADERCONFIGS = -DLINUX_GUEST
GUESTBIN	= build/zImage
else
GUESTBIN	= build/bmguest.bin
endif
ifeq ($(MONITOR), y)
GUESTLOADERCONFIGS += -DMONITOR_GUEST
endif
GUESTLOADERCONFIGS += -DGUEST_PATH=$(GUESTBIN)
ifeq ($(ANDROID), y)
GUESTLOADERCONFIGS += -DINITRD_PATH=../android_boot/uInitrd -DUSE_ANDROID_INITRD
endif
#GUEST_NUMBER = "GUEST0"
GUESTLOADERCONFIGS += -DGUEST_NUMBER=$(GUEST_NUMBER)
all: $(GUESTLOADERBIN)
clean distclean:
	rm -f $(GUESTLOADERIMG) $(GUESTLOADERBIN) build/* \
	model.lds $(OBJS)
$(GUESTLOADERIMG): $(OBJS) model.lds
	$(LD) -o $@ $(OBJS) --script=model.lds
$(GUESTLOADERBIN): $(GUESTLOADERIMG)
	$(OBJCOPY) -O binary -S $< $@
	if [ ! -d "../../build" ]; then mkdir ../../build; fi
	mv $(GUESTLOADERBIN) ../../build
ifeq ($(LINUX), y)
$(GUESTBIN):
	@echo "ERROS: Copy $@ from guestos/linux/arch/arm/boot/ after building it"
else
$(GUESTBIN):
	@echo "ERROS: Copy $@ from guestos/bmguest/ after building it"
endif
boot.o: boot.S
	$(CC) $(CPPFLAGS) $(GUESTLOADERCONFIGS) -DKCMD='$(KCMD)' -c -o $@ $<
%.o: %.c
	$(CC) $(CPPFLAGS) $(GUESTLOADERCONFIGS) -O2 -ffreestanding -I.  -c -o $@ $<
model.lds: $(LD_SCRIPT) Makefile $(GUESTBIN)
	$(CC) $(CPPFLAGS) $(GUESTLOADERCONFIGS) -E -P -C -o $@ $<
force: ;
Makefile: ;
.PHONY: all clean distclean config-default.mk
