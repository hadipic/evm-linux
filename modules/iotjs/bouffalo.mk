# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += ../../include

COMPONENT_INCLUDES += bouffalolab

## This component's src

COMPONENT_SRCS += \
	common/evm_module.c \
	common/evm_module_adc.c \
	common/evm_module_assert.c \
	common/evm_module_buffer.c \
	common/evm_module_cffi.c \
	common/evm_module_dns.c \
	common/evm_module_events.c \
	common/evm_module_fs.c \
	common/evm_module_gpio.c \
	common/evm_module_i2c.c \
	common/evm_module_libc.c \
	common/evm_module_network.c \
	common/evm_module_process.c \
	common/evm_module_timers.c \
	common/evm_module_uart.c \
	common/evm_module_wlan.c \
	common/evm_module_repl.c \
	bouffalolab/evm_main.c \
	bouffalolab/bl_module_repl.c \
	bouffalolab/bl_module_event.c \
	bouffalolab/bl_module_wlan.c \
	bouffalolab/bl_module_gpio.c \
	bouffalolab/bl_module_timers.c \
	bouffalolab/bl_module_uart.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS += common bouffalolab
