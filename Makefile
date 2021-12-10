MKDIR		:= mkdir -p
CC		:= gcc
RM		:= rm -fr

CFLAGS		:= -c -Wall -m64 -Og -nostdinc -ffreestanding
#CFLAGS		+= -D_DEBUG

INC		= include
BIN		= build

build:
	$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/boot.o src/boot.S
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/cli.o src/cli.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/io.o src/io.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/kmain.o src/kmain.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/mb2.o src/mb2.S
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/print.o src/print.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/string.o src/string.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/sys.o src/sys.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/time.o src/time.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/uart.o src/uart.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/ata.o src/ata/ata.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/ata_identify.o src/ata/ata_identify.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/ata_io.o src/ata/ata_io.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/atapi_identify.o src/ata/atapi_identify.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/ata_read.o src/ata/ata_read.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/ata_read_parttab.o src/ata/ata_read_parttab.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/ata_seek.o src/ata/ata_seek.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/ata_write.o src/ata/ata_write.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/part.o src/ata/part.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/isofs.o src/isofs/isofs.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/isofs_dump.o src/isofs/isofs_dump.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/isofs_dump_path_table.o src/isofs/isofs_dump_path_table.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/isofs_dump_primary_volume.o src/isofs/isofs_dump_primary_volume.c
	$(CC) $(CFLAGS) -I$(INC) -o $(BIN)/isofs_find.o src/isofs/isofs_find.c


clean:
	$(RM) $(BIN)
