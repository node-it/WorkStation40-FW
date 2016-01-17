/**
 * \file
 *
 * \brief SAM D11 Batman board initialization
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <compiler.h>
#include <conf_board.h>
#include <port.h>
#include <samd10_workstation40.h>

void board_init(void) WEAK __attribute__((alias("system_board_init")));

void system_board_init(void)
{
#if 0
    struct port_config pin_conf;
    struct system_pinmux_config config;

    port_get_config_defaults(&pin_conf);
    system_pinmux_get_config_defaults(&config);

    /* Analog functions are all on MUX setting B */
    config.input_pull = SYSTEM_PINMUX_PIN_PULL_NONE;
    config.mux_position = 1;

    system_pinmux_pin_set_config(ADC_PIN_0, &config);
    system_pinmux_pin_set_config(ADC_PIN_1, &config);
    system_pinmux_pin_set_config(ADC_PIN_2, &config);
    system_pinmux_pin_set_config(ADC_PIN_3, &config);
    system_pinmux_pin_set_config(ADC_PIN_4, &config);
    system_pinmux_pin_set_config(ADC_PIN_5, &config);
    system_pinmux_pin_set_config(ADC_PIN_6, &config);
    system_pinmux_pin_set_config(ADC_PIN_7, &config);

    /* Configure LEDs as outputs, turn them off */
    pin_conf.direction = PORT_PIN_DIR_OUTPUT;
    port_pin_set_config(LED1_PIN, &pin_conf);
    port_pin_set_output_level(LED1_PIN, LED1_INACTIVE);

    pin_conf.direction = PORT_PIN_DIR_INPUT;
    port_pin_set_config(BOOT_PIN, &pin_conf);

    pin_conf.direction = PORT_PIN_DIR_INPUT;
    port_pin_set_config(EXT1_PIN_1, &pin_conf);

    pin_conf.direction = PORT_PIN_DIR_INPUT;
    port_pin_set_config(EXT1_PIN_2, &pin_conf);

    pin_conf.direction = PORT_PIN_DIR_INPUT;
    port_pin_set_config(EXT1_PIN_3, &pin_conf);
#endif
}
