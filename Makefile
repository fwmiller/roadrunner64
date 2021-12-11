MKDIR	:= mkdir -p
CC	:= gcc
RM	:= rm -fr

CFLAGS	:= -c -Wall -m64 -Og -nostdinc -ffreestanding
#CFLAGS	+= -D_DEBUG

INC	= include
SRC	= src
BIN	= build

C_SRCS	:= $(sort $(shell find src/ -maxdepth 1 -type f -regex ".*\.c"))
S_SRCS	:= $(sort $(shell find src/ -maxdepth 1 -type f -regex ".*\.S"))

C_FILES	:= $(sort $(notdir $(C_SRCS)))
S_FILES	:= $(sort $(notdir $(S_SRCS)))

OBJS	:= $(foreach f,$(C_FILES),$(addprefix $(BIN)/,$(subst .c,.o,$(f))))
OBJS	+= $(foreach f,$(S_FILES),$(addprefix $(BIN)/,$(subst .S,.o,$(f))))
OBJS	:= $(sort $(OBJS))

all: $(OBJS)

clean:
	$(RM) $(BIN)

debug:
#	@echo $(C_SRCS)
#	@echo
#	@echo $(S_SRCS)
#	@echo
#	@for f in $(OBJS); do echo $$f; done

$(BIN)/%.o: $(SRC)/%.S
	@$(MKDIR) $(BIN)
#	@echo $<
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<

$(BIN)/%.o: $(SRC)/%.c
	@$(MKDIR) $(BIN)
#	@echo $<
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<
