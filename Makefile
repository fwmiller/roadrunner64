##############################################################################
#
# Directories
#
INC		:= include
SRC		:= src
BUILD		:= build
BIN		:= $(BUILD)/obj
ISOFILES	:= $(BUILD)/isofiles

##############################################################################
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
#CFLAGS		+= -g

# Debug options
#CFLAGS		+= -D_DEBUG
#CFLAGS		+= -D_DEBUG_ATA
#CFLAGS		+= -D_DEBUG_ISOFS
#CFLAGS		+= -D_DEBUG_PCI
CFLAGS		+= -D_DEBUG_ETH
#CFLAGS		+= -D_DEBUG_SHELL

LINKER_SCRIPT	:= $(SRC)/kern/link.ld
LDFLAGS		:= -nostdlib -Wl,-n,-T,$(LINKER_SCRIPT) -no-pie

INDENT_RULES	:= -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -psl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

MAX_DEPTH	:= 2

QEMU_DEBUG_OPTIONS := -s -d int
QEMU_MACH_CONFIG := -m size=4 -nographic -no-reboot -drive format=raw,file=$(BUILD)/iso.img
QEMU_NET_CONFIG := -netdev tap,id=mynet0,ifname=tap0,script=no,downscript=no -device rtl8139,netdev=mynet0,mac=26:b2:c8:eb:77:ed

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
KERNEL	:= $(BUILD)/kmain.elf

##############################################################################
#
# Boot image file
#
BOOT_IMG := $(BUILD)/iso.img

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
	@printf "Copying LWIP library\r\n"
	@cp ../roadrunner64-lwip/build/liblwip.a build
	@printf "Linking ${CYAN}$(KERNEL)${NC}\r\n"
	@$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS) build/liblwip.a
	@printf "Setup target file system ${CYAN}$(ISOFILES)${NC}\r\n"
	@$(MKDIR) $(ISOFILES)/boot/grub
	@$(CP) $(KERNEL) $(ISOFILES)/boot
	@$(CP) $(SRC)/kern/grub.cfg $(ISOFILES)/boot/grub
	@$(CP) README.md $(ISOFILES)
	@printf "Create boot image ${CYAN}$(BOOT_IMG)${NC}\r\n"
	@grub-mkrescue -o $(BOOT_IMG) $(ISOFILES)

ETH0	:= ens33

#
# Setup for tap0 networking with QEMU
#
brup:
	sudo ip link add name br0 type bridge
	sudo ip addr flush dev $(ETH0)
	sudo ip link set $(ETH0) master br0
	sudo ip tuntap add tap0 mode tap
	sudo ip link set tap0 master br0
	sudo ip link set up dev $(ETH0)
	sudo ip link set up dev tap0
	sudo ip link set up dev br0
	sudo dhclient -v br0

brdown:
	sudo ip link set tap0 nomaster
	sudo ip tuntap del tap0
	sudo ip link set $(ETH0) nomaster
	sudo ip link set down dev br0
	sudo ip link del br0
	sudo ip link set up dev $(ETH0)
	sudo dhclient -v $(ETH0)

#
# Execute using QEMU emulator
#
run: all
	@sudo qemu-system-x86_64 $(QEMU_MACH_CONFIG) $(QEMU_NET_CONFIG)

gdb: all
	@sudo qemu-system-x86_64 $(QEMU_DEBUG_OPTIONS) $(QEMU_MACH_CONFIG) $(QEMU_NET_CONFIG)

clean:
	@$(RM) $(BUILD)

#
# Indent pass of the include and src directories
#
indent: clean
	@cd $(INC);clang-format -i *.h
	@cd $(INC)/sys;clang-format -i *.h
	@clang-format -i $(C_SRCS)

wc: clean
	@wc -l $(INC)/*.h $(INC)/sys/*.h $(SRC)/asm/*.S $(SRC)/ata/*.c $(SRC)/sh/*.c $(SRC)/isofs/*.c $(SRC)/kern/*.c

debug:
	@for f in $(C_SRCS); do echo $$f; done
	@echo
	@for f in $(S_SRCS); do echo $$f; done
	@echo
	@for f in $(OBJS); do echo $$f; done

#
# Source file compilation
#
VPATH := $(SRC) $(wildcard $(SRC)/*)

$(BIN)/%.o: %.c
	@$(MKDIR) $(BUILD)
	@$(MKDIR) $(BIN)
	@printf "Compiling  ${CYAN}$<${NC}\r\n"
	@$(CC) $(CFLAGS) -I$(INC) -o $@ $<

$(BIN)/%.o: %.S
	@$(MKDIR) $(BUILD)
	@$(MKDIR) $(BIN)
	@printf "Assembling ${CYAN}$<${NC}\r\n"
	@$(CC) $(CFLAGS) -I$(INC) -o $@ $<
