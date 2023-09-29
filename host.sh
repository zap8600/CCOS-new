#!/bin/sh
#echo i686-elf
if [ ${HOSTARCH} = "riscv32" ]
then
    echo riscv32-elf
elif [ ${HOSTARCH} = "i686" ]
then
    echo i686-elf
elif [ ${HOSTARCH} = "arm32" ]
then
    echo arm-none-eabi
else
    echo "Please define HOSTARCH"
fi
