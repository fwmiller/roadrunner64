INCDIR = ../include

CC = gcc

CFLAGS = -c -Wall -m64 -Og -nostdinc -ffreestanding
CFLAGS += -D_DEBUG

LD = gcc

LDFLAGS = -nostdlib -Wl,-n,-T,link.ld -no-pie

RM = rm -fr

OBJS = boot.o mb2.o ata.o io.o kmain.o part.o print.o string.o time.o uart.o
KERNEL = kmain.elf

INDENT_RULES = -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -npsl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

all: build

build: $(OBJS) link.ld
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)
	mkdir -p isofiles/boot/grub
	cp $(KERNEL) isofiles/boot/
	cp grub.cfg isofiles/boot/grub
	grub-mkrescue -o iso.img isofiles

run: build
	qemu-system-x86_64 -nographic -no-reboot -drive format=raw,file=iso.img

clean:
	$(RM) $(OBJS) $(KERNEL) isofiles iso.img

wc: clean
	wc -l ../include/*.h *.S *.c

indent: clean
	cd ../include;indent $(INDENT_RULES) *.h
	indent $(INDENT_RULES) *.c
	rm ../include/*~ *~

.c.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<
