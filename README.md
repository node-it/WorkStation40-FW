# WorkStation40

This SAMD10 application implements an I2C expansion system to be used together with the ESP210 controller board.

It implements in I2C slave and a set of commands that allows the device to be configured and used as a multifunction peripherar. The board WorkStation40 itself implements 8 A/D channels and a number of timer / PWM channel functions.

The application relies on the ASF framework to build. To compile you need to set environment variable ASF_ROOT to where the asf framework is placed, and change the relative path in config.mk to the same.
