export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
make all && qemu-system-i386 -drive format=raw,file=./bin/disk.img