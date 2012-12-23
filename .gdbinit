#!/bin/bash
#This file is a command script to connect laod and run a program to a segger gdbserver and JLink

echo connecting to gdb server\n
target remote 127.0.0.1:2331

echo halt processor prior to loading code\n
monitor reset

echo loading .elf into processor\n
load

echo resetting processor\n
monitor reset

echo begin execution\n
monitor go

echo ready\n
