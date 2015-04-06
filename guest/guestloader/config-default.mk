#
# Main options
#
CROSS_COMPILE   ?= arm-linux-gnueabihf-

CPPFLAGS		+= -mcpu=cortex-a15 -marm -g
