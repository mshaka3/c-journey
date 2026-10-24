# ---- Settings ---------------------------------------------------
CC      := gcc
STD     := -std=c17
WARN    := -Wall -Wextra -Wpedantic -Werror
CFLAGS  := $(STD) $(WARN) -D_POSIX_C_SOURCE=200809L -MMD -MP
LDFLAGS :=

SRC_DIR := src

# MODE is "release" by default; "make debug" switches it to "debug".
MODE ?= release
ifeq ($(MODE),debug)
  CFLAGS  += -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer
  LDFLAGS += -fsanitize=address,undefined
else
  CFLAGS  += -O2
endif

BUILD := build/$(MODE)
APP   := $(BUILD)/app

# Every .c file in src/ becomes a matching .o file in build/<mode>/
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/%.o)

# ---- Targets ----------------------------------------------------
.PHONY: all debug run clean

all: $(APP)

# Link: all object files -> the program
$(APP): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

# Compile: one .c -> one .o (the | means "make sure the folder exists")
$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $@

debug:
	$(MAKE) MODE=debug

run: $(APP)
	./$(APP)

clean:
	rm -rf build

# Recompile a .c file when a header it includes changes
-include $(OBJS:.o=.d)
