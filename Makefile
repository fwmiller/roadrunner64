##############################################################################
#
# Directories
#
INC		:= include
SRC		:= src
BIN		:= build
ISOFILES	:= $(BIN)/isofiles

#
# Tools
#
MKDIR		:= mkdir -p
CC		:= gcc
LD		:= gcc
CP		:= cp
RM		:= rm -fr

##############################################################################
#
# Tool options
#
CFLAGS		:= -c -Wall -m64 -Og -nostdinc -ffreestanding
CFLAGS		+= -D_DEBUG
CFLAGS		+= -D_DEBUG_ATA
CFLAGS		+= -D_DEBUG_ISOFS

LINKER_SCRIPT	:= $(SRC)/kern/link.ld
LDFLAGS		:= -nostdlib -Wl,-n,-T,$(LINKER_SCRIPT) -no-pie

INDENT_RULES	:= -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -psl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

MAX_DEPTH	:= 2

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

NC	:= \033[0m
BLACK	:= \033[0;30m
RED	:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
PURPLE	:= \033[0;35m
CYAN	:= \033[0;36m
WHITE	:= \033[0;37m

.PHONY: run clean indent wc debug

all: $(OBJS) $(LINKER_SCRIPT)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)
	$(MKDIR) $(ISOFILES)/boot/grub
	$(CP) $(KERNEL) $(ISOFILES)/boot
	$(CP) $(SRC)/kern/grub.cfg $(ISOFILES)/boot/grub
	$(CP) README.md $(ISOFILES)
	grub-mkrescue -o $(BIN)/iso.img $(ISOFILES)

#
# Execute using QEMU emulator
#
run: all
	@qemu-system-x86_64 -m size=4 -nographic -no-reboot -drive format=raw,file=$(BIN)/iso.img

clean:
	@$(RM) $(BIN)

#
# Indent pass of the include and src directories
#
indent: clean
	@cd $(INC);clang-format -i *.h
	@cd $(INC)/sys;clang-format -i *.h
	@clang-format -i $(C_SRCS)

wc: clean
	@wc -l $(INC)/*.h $(INC)/sys/*.h $(SRC)/asm/*.S $(SRC)/ata/*.c $(SRC)/cli/*.c $(SRC)/isofs/*.c $(SRC)/kern/*.c

debug:
	@for f in $(C_SRCS); do echo $$f; done
	@echo
	@for f in $(S_SRCS); do echo $$f; done
	@echo
	@for f in $(OBJS); do echo $$f; done

#
# Assembly source file compilation
#
$(BIN)/%.o: $(SRC)/asm/%.S
	@$(MKDIR) $(BIN)
	@printf "Assembling ${CYAN}$<${NC}\r\n"
	@$(CC) $(CFLAGS) -I$(INC) -o $@ $<

#
# C source file compilation
#
$(BIN)/%.o: $(SRC)/*/%.c
	@$(MKDIR) $(BIN)
	@printf "Compiling  ${CYAN}$<${NC}\r\n"
	@$(CC) $(CFLAGS) -I$(INC) -o $@ $<

$(BIN)/%.o: $(SRC)/%.c
	@$(MKDIR) $(BIN)
	@printf "Compiling ${CYAN}$<${NC}\r\n"
	@$(CC) $(CFLAGS) -I$(INC) -o $@ $<
