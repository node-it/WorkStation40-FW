/*
 * ----------------------------------------------------------------------------
 *            _____ _           _                   _
 *           | ____| | ___  ___| |_ _ __ ___  _ __ (_) ___
 *           |  _| | |/ _ \/ __| __| '__/ _ \| '_ \| |/ __|
 *           | |___| |  __/ (__| |_| | | (_) | | | | | (__
 *           |_____|_|\___|\___|\__|_|  \___/|_| |_|_|\___|
 *            ____                   _   ____
 *           / ___|_      _____  ___| |_|  _ \ ___  __ _ ___
 *           \___ \ \ /\ / / _ \/ _ \ __| |_) / _ \/ _` / __|
 *            ___) \ V  V /  __/  __/ |_|  __/  __/ (_| \__ \
 *           |____/ \_/\_/ \___|\___|\__|_|   \___|\__,_|___/
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <pontus@sweetpeas.se> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return - Pontus Oldberg
 * ----------------------------------------------------------------------------
 *
 * = SAMD10 I2C server =
 *
 * This I2C server opens up the entire SAMD10 chip to be used anyway anyone likes.
 * The server only has two commands, read one 32 bit memory location and write one
 * 32 bit memory location !
 * Effectively this means that the user can access any memory location and/or any
 * control register in the device, thus exposing all the functionality that the
 * device has.
 *
 * == I2C operations ==
 *
 * === Read memory location ===
 * A read operation consists of an initial 32 bit write operation that contains the
 * memory location that should be read, followed by a a 32 bit read operation of
 * the value.
 *
 * === Write memory location ===
 * A write operation consists of an initial 32 bit write operation that contains
 * the memory location that shall be written. This is immediatly followed by a
 * 32 bit write operation with the data that shall be written.
 *
 * === Caution ===
 * Read and write operation must be carried out on a valid function register or
 * memory address, furthermore the address that you supply must also be on an even
 * 32 bit boundary, otherwise the device will crash and must be reset.
 * Future releases will include a fault detect mechanism that will catch this and
 * signal an interrupt to the ESP210, but for now, do take care when programming.
 */
#include <asf.h>
#include "board/samd10_workstation40.h"

static void configure_i2c_slave(void);
static struct i2c_slave_packet packet;

/* I2C Register file definitions */
#define TRANSACTION_LENGTH    8
/* Address of the slave */
#define SLAVE_ADDRESS         0x12

struct i2c_slave_module i2c_slave_instance;

// The first byte in the read buffer is always the register address.
static uint8_t read_buffer[TRANSACTION_LENGTH];
static uint8_t write_buffer[TRANSACTION_LENGTH];

#if defined(DEBUG)
static volatile int dummy = 0;
#define LED_PIN         PIN_PA02
#define LED_MASK        (1U << (LED_PIN & 0x1F))
volatile PortGroup *boot_port = (volatile PortGroup *)(&(PORT->Group[LED_PIN / 32]));
#endif
/*****************************************************************************/
/**                                                                         **/
/**                                 FUNCTIONS                               **/
/**                                                                         **/
/*****************************************************************************/
/*
 * Global configuration of the i2c interface
 * In this application the I2C interface is operating in slave mode.
 */
static void configure_i2c_slave(void)
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

static void handle_i2c_write(void)
{
  // The read buffer now contains valid data for writing information to the device
  uint32_t mem;
  uint32_t *mem_ptr;
  uint32_t value;

  // Collect the memory pointer
  MSB0W(mem) = read_buffer[0];
  MSB1W(mem) = read_buffer[1];
  MSB2W(mem) = read_buffer[2];
  MSB3W(mem) = read_buffer[3];

  // Collect the value
  MSB0W(value) = read_buffer[4];
  MSB1W(value) = read_buffer[5];
  MSB2W(value) = read_buffer[6];
  MSB3W(value) = read_buffer[7];

  // And finally write the value to the memory
  mem_ptr = (uint32_t *)mem;
  *mem_ptr = value;
}

static void handle_i2c_read(void)
{
  // The read buffer now holds the register that the client wants to read
  uint32_t mem;
  uint32_t *mem_ptr;
  uint32_t value;

  // Collect the memory pointer
  MSB0W(mem) = read_buffer[0];
  MSB1W(mem) = read_buffer[1];
  MSB2W(mem) = read_buffer[2];
  MSB3W(mem) = read_buffer[3];

  // Now get the value from the memory pointer
  mem_ptr = (uint32_t *)mem;
  value = *mem_ptr;

  // And pack it into the buffer.
  write_buffer[0] = (value >> 24) & 0xff;
  write_buffer[1] = (value >> 16) & 0xff;
  write_buffer[2] = (value >> 8) & 0xff;
  write_buffer[3] = value & 0xff;
}

int main(void)
{
  enum i2c_slave_direction dir;

	system_init();

#if defined(DEBUG)
  uint32_t i,j;
  /* Enable the board LED pin and make it an output */
  boot_port->DIRSET.reg = LED_MASK;
  boot_port->OUTCLR.reg = LED_MASK;

  /* Just make a little blinky to indicate we got started */
  for (i=0;i<10;i++) {
    for(j=0;j<100000;j++) {
      dummy++;
    }
    boot_port->OUTTGL.reg = LED_MASK;
  }
#endif

	/* Initialize the i2c block and callbacks */
	configure_i2c_slave();

  // Blocking I2C arbiter
	while (true) {
    dir = i2c_slave_get_direction_wait(&i2c_slave_instance);
    if (dir == I2C_SLAVE_DIRECTION_READ) {
      packet.data_length = 8;
      packet.data = read_buffer;
      if (STATUS_OK == i2c_slave_read_packet_wait(&i2c_slave_instance, &packet)) {
        handle_i2c_write();
      } else {
        handle_i2c_read();
      }
    } else if (dir == I2C_SLAVE_DIRECTION_WRITE) {
      packet.data_length = 4;
      packet.data = write_buffer;
      i2c_slave_write_packet_wait(&i2c_slave_instance, &packet);
    }
  }
}
