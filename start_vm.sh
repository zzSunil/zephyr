#!/bin/bash

qemu-system-riscv64 -machine virt -nographic -m 256 -bios ../opensbi/share/opensbi/lp64/generic/firmware/fw_jump.bin -kernel build/zephyr/zephyr.elf
