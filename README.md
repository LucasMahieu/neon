neon
====

This project is the basis for the Freescale MKL25Z128VLK4 Cortex-M0+ microcontroller that handles the real-time clock and power sequencing.

C language project using Linaro GCC. Uses some setup files from Freescale, and the Freescale linker file. Project can be loaded on to hardware using a Segger J-Link dongle in SWD mode.

The toolchain used is built by running summon-arm-toolchain.sh. This script is taken from the  https://github.com/esden/summon-arm-toolchain project. Commit: 0570ac76c0fb8c3b841c39513ac0c908a833f401

The toolchain script was modified to disable the usage of openocd and libstm32 and libopencm3.

As of commit e8550b91c4426df6f768f184df4f139696c52aef this project uses an SCons build file.
To build the project simply run ./scons/scons.py
To clean the project simply run ./scons/scons.py -c

