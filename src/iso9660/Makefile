INCDIR = ../../include

CC = gcc

CFLAGS = -c -Wall -m64 -Og -nostdinc -ffreestanding
CFLAGS += -D_DEBUG

AR = ar -r
RANLIB = ranlib
RM = rm -fr

OBJS = iso9660.o iso9660_dump.o
TGT = libiso9660.a

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
