INC	= include
SRC	= src
BIN	= build

MKDIR	:= mkdir -p
CC	:= gcc
LD	:= gcc
CP	:= cp
RM	:= rm -fr

CFLAGS	:= -c -Wall -m64 -Og -nostdinc -ffreestanding
#CFLAGS	+= -D_DEBUG
LDFLAGS	:= -nostdlib -Wl,-n,-T,$(SRC)/link.ld -no-pie

C_SRCS	:= $(shell find src/ -maxdepth 1 -type f -regex ".*\.c")
C_FILES	:= $(sort $(notdir $(C_SRCS)))

S_SRCS	:= $(shell find src/ -maxdepth 1 -type f -regex ".*\.S")
S_FILES	:= $(sort $(notdir $(S_SRCS)))

OBJS	:= $(foreach f,$(C_FILES),$(addprefix $(BIN)/,$(subst .c,.o,$(f))))
OBJS	+= $(foreach f,$(S_FILES),$(addprefix $(BIN)/,$(subst .S,.o,$(f))))
OBJS	:= $(sort $(OBJS))

KERNEL	:= $(BIN)/kmain.elf

all: $(OBJS) $(SRC)/link.ld
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)
	$(MKDIR) $(BIN)/isofiles/boot/grub
	$(CP) $(KERNEL) $(BIN)/isofiles/boot/
	$(CP) $(SRC)/grub.cfg $(BIN)/isofiles/boot/grub
	grub-mkrescue -o $(BIN)/iso.img $(BIN)/isofiles

run: all
	qemu-system-x86_64 -nographic -no-reboot -drive format=raw,file=$(BIN)/iso.img

clean:
	$(RM) $(BIN)

debug:
	@for f in $(C_SRCS); do echo $$f; done
	@echo
	@for f in $(S_SRCS); do echo $$f; done
	@echo
	@for f in $(OBJS); do echo $$f; done

$(BIN)/%.o: $(SRC)/%.S
	@$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<

$(BIN)/%.o: $(SRC)/%.c
	@$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<
