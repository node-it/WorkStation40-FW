/**
 * \file
 *
 * \brief SAM SERCOM I2C Slave Quick Start Guide with Callbacks
 *
 * Copyright (C) 2013-2015 Atmel Corporation. All rights reserved.
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

#include <asf.h>
#include <adc.h>
#include <adc_callback.h>
#include "board/samd10_workstation40.h"

void i2c_read_request_callback(
		struct i2c_slave_module *const module);
void i2c_write_request_callback(
		struct i2c_slave_module *const module);
void configure_i2c_slave(void);
void configure_i2c_slave_callbacks(void);

void configure_adc(void);
void configure_adc_callbacks(void);
void adc_complete_callback(
                struct adc_module *const module);
void reconfigure_adc(struct adc_config *config);

static struct i2c_slave_packet packet;

/* A I2C transaction is composed of a number of different
 * use cases. These are identified so far.
 *
 * 1. Write to register file.
 *    This is a transaction that is built up of three or more
 *    bytes that comes over the I2C line.
 *
 * 2.
 */ 
enum i2c_states {
	I2C_OFFSET_WAIT = 0x01,
	I2C_DATA_WAIT,
};

/*
 * ADC Defintions and settings
 */
#define NUM_ADC_CHANNELS	8
#define ADC_SAMPLES 1
uint16_t adc_result_buffer[ADC_SAMPLES];
struct adc_module adc_instance;
volatile bool adc_read_done = false;
struct adc_config config_adc;
uint8_t adc_ix = 0;

/*
 * I2C Register file definitions
 */
#define REGISTER_FILE_LENGTH 33
/* Address of the slave */
#define SLAVE_ADDRESS 0x12
struct i2c_slave_module i2c_slave_instance;

enum boot_control {
	NOT_USED,
	REBOOT_NORMAL,			// Just reboots the system
	REBOOT_INTO_BOOTLOADER		// Boots into bootloader
};

struct adc_control_reg {
	uint8_t enable:1;		// Enable disable ADC
	uint8_t mode:2;			// Operation mode
};

enum adc_control {
	ADC_ENABLE = 0x01,		// Enable/Disable the ADC
};

enum adc_operating_mode {
	ADC_10BITS = 0x00,
	ADC_12BITS = 0x01,
	ADC_16BITS = 0x02
};

static uint8_t adc_chan_map[] = {
	ADC_PIN_0, ADC_PIN_1, ADC_PIN_2, ADC_PIN_3,
	ADC_PIN_4, ADC_PIN_5, ADC_PIN_6, ADC_PIN_7
};

struct register_file_description {
	uint8_t packet_start;		// I2C transaction length
	uint8_t packet_length;		// Length of transaction
	uint8_t adc_control;		// Adc control register
	uint16_t adc[NUM_ADC_CHANNELS];	// Adc values
	uint8_t boot_control;		// Controls booting
};
struct register_file_description reg_file;

static uint8_t register_file[REGISTER_FILE_LENGTH];

/*
 * Call back function for the adc
 */
void adc_complete_callback(struct adc_module *const module)
{
        adc_read_done = true;
	adc_read(&adc_instance, &reg_file.adc[adc_ix]);
	if (++adc_ix == NUM_ADC_CHANNELS) {
		adc_ix = 0;
	}
	config_adc.positive_input  = adc_chan_map[0];
	adc_start_conversion(&adc_instance);
}

/*
 * Global configuration for the ADC
 */
void configure_adc(void)
{
        adc_get_config_defaults(&config_adc);

	config_adc.gain_factor     = ADC_GAIN_FACTOR_1X;
        config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV8;
        config_adc.reference       = ADC_REFERENCE_INTVCC1;
        config_adc.positive_input  = adc_chan_map[0];
	config_adc.negative_input  = ADC_NEGATIVE_INPUT_IOGND;
        config_adc.resolution      = ADC_RESOLUTION_12BIT;

        adc_init(&adc_instance, ADC, &config_adc);

        adc_enable(&adc_instance);
}

/*
 * Reconfiguration of the adc
 */
void reconfigure_adc(struct adc_config *config)
{
	adc_disable(&adc_instance);
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}

/*
 * ADC call back configuration
 */
void configure_adc_callbacks(void)
{
        adc_register_callback(&adc_instance,
                        adc_complete_callback, ADC_CALLBACK_READ_BUFFER);
        adc_enable_callback(&adc_instance, ADC_CALLBACK_READ_BUFFER);
}



/*
 * Call back function for read operations
 */
void i2c_read_request_callback(
		struct i2c_slave_module *const module)
{
	packet.data_length = REGISTER_FILE_LENGTH;
	packet.data        = register_file;

	i2c_slave_write_packet_job(module, &packet);
}

/*
 * Call back function for write operations
 */
void i2c_write_request_callback(
		struct i2c_slave_module *const module)
{
	packet.data_length = REGISTER_FILE_LENGTH;
	packet.data        = register_file;

	if (i2c_slave_read_packet_job(module, &packet) != STATUS_OK) {
		/* What to do if something goes wrong */
	}
}

/*
 * Global configuration of the i2c interface
 * In this application the I2C interface is operating in slave mode.
 */
void configure_i2c_slave(void)
{
	/* Initialize config structure and module instance. */
	struct i2c_slave_config config_i2c_slave;
	i2c_slave_get_config_defaults(&config_i2c_slave);
	
	/* Change address and address_mode. */
	config_i2c_slave.address      = SLAVE_ADDRESS;
	config_i2c_slave.address_mode = I2C_SLAVE_ADDRESS_MODE_MASK;
	
	/* Initialize and enable device with config. */
	i2c_slave_init(&i2c_slave_instance, SERCOM2, &config_i2c_slave);

	i2c_slave_enable(&i2c_slave_instance);
}

/*
 * Register call back functions for i2c read and write operations
 */
void configure_i2c_slave_callbacks(void)
{
	/* Register and enable callback functions */
	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_request_callback,
			I2C_SLAVE_CALLBACK_READ_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,
			I2C_SLAVE_CALLBACK_READ_REQUEST);

	i2c_slave_register_callback(&i2c_slave_instance, i2c_write_request_callback,
			I2C_SLAVE_CALLBACK_WRITE_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,
			I2C_SLAVE_CALLBACK_WRITE_REQUEST);
}

int main(void)
{
	system_init();

	/* Configure the ADC */
        configure_adc();
        configure_adc_callbacks();
	system_interrupt_enable_global();

	/* Initialize the i2c block and callbacks */
	configure_i2c_slave();
	configure_i2c_slave_callbacks();

	adc_read_buffer_job(&adc_instance, adc_result_buffer, ADC_SAMPLES);
	
	while (true) {
		/* Infinite loop while waiting for I2C master interaction */
	}
}
