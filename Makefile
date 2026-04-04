FILES = ./build/kernel.asm.o ./build/kernel.o ./build/terminal.o ./build/idt.o ./build/isr.o ./build/isr.asm.o ./build/irq.asm.o ./build/irq.o ./build/pic.o ./build/io.asm.o
FLAGS = -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all:
	nasm -f bin ./src/boot.asm -o ./bin/boot.bin
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o
	nasm -f elf -g ./src/Interrupts/isr.asm -o ./build/isr.asm.o
	nasm -f elf -g ./src/Interrupts/irq.asm -o ./build/irq.asm.o 
	nasm -f elf -g ./src/IO/io.asm -o ./build/io.asm.o

	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Terminal/terminal.c -o ./build/terminal.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Interrupts/idt.c -o ./build/idt.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Interrupts/isr.c -o ./build/isr.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Interrupts/pic.c -o ./build/pic.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Interrupts/irq.c -o ./build/irq.o

	i686-elf-ld -g -relocatable $(FILES) -o ./build/mergedKernel.o
	i686-elf-gcc $(FLAGS) -T ./linker.ld -o ./bin/kernel.elf -ffreestanding -O0 -nostdlib ./build/mergedKernel.o
	i686-elf-objcopy -O binary ./bin/kernel.elf ./bin/kernel.bin

	dd if=./bin/boot.bin of=./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=8 >> ./bin/os.bin


clean:
	rm -f ./build/*.o 
	rm -f ./bin/*.bin 
	rm -f ./bin/*.elf