# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += ../../include
COMPONENT_ADD_INCLUDEDIRS += ./mujs
COMPONENT_ADD_INCLUDEDIRS += .

## This component's src

COMPONENT_SRCS += \
	evm.c \
	mujs/one.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS += mujs
