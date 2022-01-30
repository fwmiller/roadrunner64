##############################################################################
#
# Directories
#
INC	:= include
SRC	:= src
BIN	:= build

#
# Tools
#
MKDIR	:= mkdir -p
CC	:= gcc
LD	:= gcc
CP	:= cp
RM	:= rm -fr

##############################################################################
#
# Tool options
#
CFLAGS	:= -c -Wall -m64 -Og -nostdinc -ffreestanding
CFLAGS	+= -D_DEBUG

LINKER_SCRIPT	:= link.ld
LDFLAGS		:= -nostdlib -Wl,-n,-T,$(SRC)/$(LINKER_SCRIPT) -no-pie

INDENT_RULES := -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -psl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

MAX_DEPTH := 2

##############################################################################
#
# C file sets
#
C_SRCS	:= $(shell find $(SRC)/ -maxdepth $(MAX_DEPTH) -type f -regex ".*\.c")
C_FILES	:= $(sort $(notdir $(C_SRCS)))

##############################################################################
#
# Assembly file sets
#
S_SRCS	:= $(shell find $(SRC)/ -maxdepth $(MAX_DEPTH) -type f -regex ".*\.S")
S_FILES	:= $(sort $(notdir $(S_SRCS)))

##############################################################################
#
# Object files
#
OBJS	:= $(foreach f,$(C_FILES),$(addprefix $(BIN)/,$(subst .c,.o,$(f))))
OBJS	+= $(foreach f,$(S_FILES),$(addprefix $(BIN)/,$(subst .S,.o,$(f))))
OBJS	:= $(sort $(OBJS))

##############################################################################
#
# Kernel file
#
KERNEL	:= $(BIN)/kmain.elf

##############################################################################
#
# Rules
#
all: $(OBJS) $(SRC)/$(LINKER_SCRIPT)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)
	$(MKDIR) $(BIN)/isofiles/boot/grub
	$(CP) $(KERNEL) $(BIN)/isofiles/boot/
	$(CP) $(SRC)/grub.cfg $(BIN)/isofiles/boot/grub
	grub-mkrescue -o $(BIN)/iso.img $(BIN)/isofiles

#
# Execute using QEMU emulator
#
run: all
	qemu-system-x86_64 -m size=4 -nographic -no-reboot -drive format=raw,file=$(BIN)/iso.img

clean:
	$(RM) $(BIN)

#
# Indent pass of the include and src directories
#
indent: clean
	cd $(INC);indent $(INDENT_RULES) *.h
	cd $(INC)/sys;indent $(INDENT_RULES) *.h
	cd $(SRC);indent $(INDENT_RULES) *.c
	cd $(SRC)/ata;indent $(INDENT_RULES) *.c
	cd $(SRC)/isofs;indent $(INDENT_RULES) *.c
	rm $(INC)/*~ $(INC)/sys/*~ $(SRC)/*~ $(SRC)/ata/*~ $(SRC)/isofs/*~

wc: clean
	wc -l $(INC)/*.h $(INC)/sys/*.h $(SRC)/*.S $(SRC)/*.c

debug:
	@for f in $(C_SRCS); do echo $$f; done
	@echo
	@for f in $(S_SRCS); do echo $$f; done
	@echo
	@for f in $(OBJS); do echo $$f; done

#
# Assembly source file compilation
#
$(BIN)/%.o: $(SRC)/%.S
	@$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<

#
# C source file compilation
#
$(BIN)/%.o: $(SRC)/*/%.c
	@$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<

$(BIN)/%.o: $(SRC)/%.c
	@$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<
