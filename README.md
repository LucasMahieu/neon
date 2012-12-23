neon
====

This project is the basis for the Freescale MKL25Z128VLK4 Cortex-M0+ microcontroller that handles the real-time clock and power sequencing.

C language project using Linaro GCC. Uses some setup files from Freescale, and the Freescale linker file. Project can be loaded on to hardware using a Segger J-Link dongle in SWD mode.

The toolchain used is built by running summon-arm-toolchain.sh. This script is taken from the  https://github.com/esden/summon-arm-toolchain project. Commit: 0570ac76c0fb8c3b841c39513ac0c908a833f401

The toolchain script was modified to remove the usage of openocd and libstm32 and libopencm3.

Presently the project is built using a homebrew script to call all compiler commands. It isn't very good and should be replaced.
