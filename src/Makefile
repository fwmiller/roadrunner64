INCDIR = ../include
LIBDIR = -L./ata

CC = gcc

CFLAGS = -c -Wall -m64 -Og -nostdinc -ffreestanding
CFLAGS += -D_DEBUG

LD = gcc

LDFLAGS = -nostdlib -Wl,-n,-T,link.ld -no-pie

RM = rm -fr

# boot.o and mb2.o must be first
OBJS = boot.o mb2.o cli.o io.o iso9660.o kmain.o print.o string.o sys.o time.o uart.o
LIBS = -lata
KERNEL = kmain.elf

INDENT_RULES = -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -psl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

all: build

build: $(OBJS) link.ld
	cd ata; make
	$(LD) $(LDFLAGS) $(LIBDIR) -o $(KERNEL) $(OBJS) $(LIBS)
	mkdir -p isofiles/boot/grub
	cp $(KERNEL) isofiles/boot/
	cp grub.cfg isofiles/boot/grub
	grub-mkrescue -o iso.img isofiles

run: build
	qemu-system-x86_64 -nographic -no-reboot -drive format=raw,file=iso.img

clean:
	cd ata; make clean
	$(RM) $(OBJS) $(KERNEL) isofiles iso.img

wc: clean
	wc -l ../include/*.h *.S *.c

indent: clean
	cd ../include;indent $(INDENT_RULES) *.h
	cd ../include/sys;indent $(INDENT_RULES) *.h
	cd ata;indent $(INDENT_RULES) *.c
	indent $(INDENT_RULES) *.c
	rm ../include/*~ ../include/sys/*~ ./ata/*~ *~

.c.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<
