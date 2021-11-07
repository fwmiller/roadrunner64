INCDIR = ../../include

CC = gcc

CFLAGS = -c -Wall -m64 -Og -nostdinc -ffreestanding
CFLAGS += -D_DEBUG

AR = ar -r
RANLIB = ranlib
RM = rm -fr

OBJS = ata.o ata_identify.o ata_io.o ata_read.o ata_read_mbr.o ata_read_parttab.o ata_seek.o ata_write.o atapi_identify.o part.o
TGT = libata.a

INDENT_RULES = -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -npsl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

all: build

build: $(OBJS)
	$(AR) $(TGT) $(OBJS)
	$(RANLIB) $(TGT)

clean:
	$(RM) $(OBJS) $(TGT)

wc: clean
	wc -l *.c

indent: clean
	indent $(INDENT_RULES) *.c
	$(RM) ../include/*~ *~

.c.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<

.S.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<
