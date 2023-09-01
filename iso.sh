#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/ccos.kernel isodir/boot/ccos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "ccos" {
	multiboot /boot/ccos.kernel
}
EOF
grub-mkrescue -o ccos.iso isodir
