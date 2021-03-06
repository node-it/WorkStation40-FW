#
# Copyright (c) 2011 Atmel Corporation. All rights reserved.
#
# \asf_license_start
#
# \page License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
#    Atmel microcontroller product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# \asf_license_stop
#

# Path to top level ASF directory relative to this project directory.
PRJ_PATH = ../xdk-asf-3.24.2

# Target CPU architecture: cortex-m3, cortex-m4
ARCH = cortex-m0plus

# Target part: none, sam3n4 or sam4l4aa
PART = samd10d14am

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET_FLASH = workstation40.elf
TARGET_SRAM = workstation40.elf

# Some path magic
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

# List of C source files.
# All C source paths are relative to PRJ_PATH
CSRCS = \
       ../$(current_dir)/workstation40.c                  \
       ../$(current_dir)/board/board_init.c               \
       common/utils/interrupt/interrupt_sam_nvic.c        \
       sam0/drivers/adc/adc_sam_d_r/adc.c                 \
       sam0/drivers/adc/adc_sam_d_r/adc_callback.c        \
       sam0/drivers/port/port.c                           \
       sam0/drivers/sercom/i2c/i2c_sam0/i2c_slave.c       \
       sam0/drivers/sercom/sercom.c                       \
       sam0/drivers/sercom/sercom_interrupt.c             \
       sam0/drivers/system/clock/clock_samd10_d11/clock.c \
       sam0/drivers/system/clock/clock_samd10_d11/gclk.c  \
       sam0/drivers/system/interrupt/system_interrupt.c   \
       sam0/drivers/system/pinmux/pinmux.c                \
       sam0/drivers/system/system.c                       \
       sam0/utils/cmsis/samd10/source/gcc/startup_samd10.c \
       sam0/utils/cmsis/samd10/source/system_samd10.c     \
       sam0/utils/syscalls/gcc/syscalls.c

# List of assembler source files.
ASSRCS =


# List of include paths.
# All include file paths are relative to PRJ_PATH
INC_PATH = \
       ../$(current_dir)                                  \
       ../$(current_dir)/board                            \
       common/boards                                      \
       common/utils                                       \
       sam0/boards                                        \
       sam0/drivers/adc                                   \
       sam0/drivers/adc/adc_sam_d_r                       \
       sam0/drivers/port                                  \
       sam0/drivers/sercom                                \
       sam0/drivers/sercom/i2c                            \
       sam0/drivers/sercom/i2c/i2c_sam0                   \
       sam0/drivers/sercom/i2c/quick_start_slave_callback \
       sam0/drivers/system                                \
       sam0/drivers/system/clock                          \
       sam0/drivers/system/clock/clock_samd10_d11         \
       sam0/drivers/system/interrupt                      \
       sam0/drivers/system/interrupt/system_interrupt_samd10_d11 \
       sam0/drivers/system/pinmux                         \
       sam0/drivers/system/power                          \
       sam0/drivers/system/power/power_sam_d_r            \
       sam0/drivers/system/reset                          \
       sam0/drivers/system/reset/reset_sam_d_r            \
       sam0/utils                                         \
       sam0/utils/cmsis/samd10/include                    \
       sam0/utils/cmsis/samd10/source                     \
       sam0/utils/header_files                            \
       sam0/utils/preprocessor                            \
       thirdparty/CMSIS/Include                           \
       thirdparty/CMSIS/Lib/GCC

# Additional search paths for libraries.
LIB_PATH =  \
       thirdparty/CMSIS/Lib/GCC

# List of libraries to use during linking.
LIBS =  \
       arm_cortexM0l_math

# Path relative to top level directory pointing to a linker script.
USE_LOCAL_LINK_SCRIPT = true
LINKER_SCRIPT_FLASH = workstation40.ld
#LINKER_SCRIPT_FLASH = sam0/utils/linker_scripts/samd10/gcc/samd10d14am_flash.ld
#LINKER_SCRIPT_SRAM  = sam0/utils/linker_scripts/samd10/gcc/samd10d14am_sram.ld

# Path relative to top level directory pointing to a linker script.
DEBUG_SCRIPT_FLASH = sam0/boards/samd11_xplained_pro/debug_scripts/gcc/samd11_xplained_pro_flash.gdb
DEBUG_SCRIPT_SRAM  = sam0/boards/samd11_xplained_pro/debug_scripts/gcc/samd11_xplained_pro_sram.gdb

# Project type parameter: all, sram or flash
PROJECT_TYPE        = flash

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS =

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os
OPTIMIZATION = -Os

# Extra flags to use when archiving.
ARFLAGS =

# Extra flags to use when assembling.
ASFLAGS =

# Extra flags to use when compiling.
CFLAGS =

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
       -D ADC_CALLBACK_MODE=true                          \
       -D ARM_MATH_CM0PLUS=true                           \
       -D BOARD=SAMD11_XPLAINED_PRO                       \
       -D I2C_SLAVE_CALLBACK_MODE=false                   \
       -D __SAMD10D14AM__

# Extra flags to use when linking
LDFLAGS = \

# Pre- and post-build commands
PREBUILD_CMD =
POSTBUILD_CMD = cp workstation40.bin fw.bin; xxd -i fw.bin fw.h
