FILES = ./build/kernel.asm.o ./build/kernel.o ./build/terminal.o ./build/idt.o ./build/isr.o ./build/isr.asm.o ./build/irq.asm.o ./build/irq.o ./build/pic.o ./build/io.asm.o ./build/pmm.o ./build/Emalloc.o ./build/paging.o ./build/enable_paging.asm.o ./build/process.o ./build/context_switch.asm.o ./build/scheduler.o ./build/tlb_flush.asm.o ./build/elf.o ./build/hello_elf.o
FLAGS = -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all:
	nasm -f bin ./src/boot.asm -o ./bin/boot.bin
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o
	nasm -f elf -g ./src/Interrupts/isr.asm -o ./build/isr.asm.o
	nasm -f elf -g ./src/Interrupts/irq.asm -o ./build/irq.asm.o 
	nasm -f elf -g ./src/IO/io.asm -o ./build/io.asm.o
	nasm -f elf -g ./src/Memory/enable_paging.asm -o ./build/enable_paging.asm.o
	nasm -f elf -g ./src/Memory/tlb_flush.asm -o ./build/tlb_flush.asm.o
	nasm -f elf -g ./src/Process/context_switch.asm -o ./build/context_switch.asm.o

	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Terminal/terminal.c -o ./build/terminal.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Interrupts/idt.c -o ./build/idt.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Interrupts/isr.c -o ./build/isr.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Interrupts/pic.c -o ./build/pic.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Interrupts/irq.c -o ./build/irq.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Memory/pmm.c -o ./build/pmm.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Memory/Emalloc.c -o ./build/Emalloc.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Memory/paging.c -o ./build/paging.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Process/process.c -o ./build/process.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Process/scheduler.c -o ./build/scheduler.o
	i686-elf-gcc -I./src $(FLAGS) -std=gnu99 -c ./src/Loader/elf.c -o ./build/elf.o

	i686-elf-gcc -ffreestanding -nostdlib -T user_linker.ld ./src/User/hello.c -o ./build/hello.elf
	i686-elf-objcopy -I binary -O elf32-i386 -B i386 ./build/hello.elf ./build/hello_elf.o

	i686-elf-ld -g -relocatable $(FILES) -o ./build/mergedKernel.o
	i686-elf-gcc $(FLAGS) -T ./linker.ld -o ./bin/kernel.elf -ffreestanding -O0 -nostdlib ./build/mergedKernel.o
	i686-elf-objcopy -O binary ./bin/kernel.elf ./bin/kernel.bin

	dd if=./bin/boot.bin of=./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=32 >> ./bin/os.bin


clean:
	rm -f ./build/*.o 
	rm -f ./bin/*.bin 
	rm -f ./bin/*.elf