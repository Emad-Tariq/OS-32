FILES = ./build/kernel.asm.o ./build/kernel.o ./build/terminal.o
FLAGS = -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all:
	nasm -f bin ./src/boot.asm -o ./bin/boot.bin
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o

	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Terminal/terminal.c -o ./build/terminal.o
	i686-elf-ld -g -relocatable $(FILES) -o ./build/mergedKernel.o
	i686-elf-gcc $(FLAGS) -T ./linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/mergedKernel.o
	i686-elf-gcc $(FLAGS) -T ./linker.ld -o ./bin/kernel.elf -ffreestanding -O0 -nostdlib ./build/mergedKernel.o
	i686-elf-objcopy -O binary ./bin/kernel.elf ./bin/kernel.bin

	dd if=./bin/boot.bin of=./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=8 >> ./bin/os.bin


clean:
	rm -f ./bin/boot.bin
	rm -f ./bin/kernel.bin
	rm -f ./bin/os.bin
	rm -f ./build/kernel.os
	rm -f ./build/kernel.asm.os
	rm -f ./build/mergedKernel.o
	rm -f ./build/terminal.o