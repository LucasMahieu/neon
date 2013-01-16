neon
====

This project is the basis for the Freescale MKL25Z128VLK4 Cortex-M0+ microcontroller that handles the real-time clock and power sequencing.

C language project using Linaro GCC. Uses some setup files from Freescale, and the Freescale linker file. Project can be loaded on to hardware using a Segger J-Link dongle in SWD mode.

The toolchain used is built by running summon-arm-toolchain.sh. This script is taken from the  https://github.com/esden/summon-arm-toolchain project. Commit: c207a7e6d88aa0b17617928f291f21789aa71766

The toolchain script was modified to disable the usage of openocd and libstm32 and libopencm3.
The toolchain script was also modified to build newlib after gcc then rebuild gcc with newlib.
I don't know if this is strictly necessary, but it works. More testing is needed.

As of commit e8550b91c4426df6f768f184df4f139696c52aef this project uses an SCons build file.
To build the project simply run ./scons/scons.py
To clean the project simply run ./scons/scons.py -c

Processor to be set up as I2C slave 0x84.

