objs = start.o main.o 

ledc.bin:$(objs)
	arm-linux-gnueabihf-ld -Timx6u.lds $^ -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g led.elf $@
	arm-linux-gnueabihf-objdump -D -m arm led.elf > led.dis

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c  -o $@ $<

%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c  -o $@ $<

clean:
	rm -rf *.o ledc.bin led.elf led.dis