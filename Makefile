BIN       := schrodinger-sim
PREFIX    ?= /usr/local

BIN_DIR  := bin
SCRIPT_DIR := scripts
SRC_DIR   := src
INC_DIR   := include
TEST_DIR  := tests


SRCS      := $(filter-out $(SRC_DIR)/scratch.c, $(wildcard $(SRC_DIR)/*.c))
OBJS      := $(SRCS:.c=.o)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(TEST_SRCS:.c=.o)
CC        ?= cc
CFLAGS    := -std=c99 -Wall -Wextra -Werror -I$(INC_DIR) -O2
LDLIBS    := -lm


$(BIN): $(OBJS)
	$(CC) $^ -o $(BIN_DIR)/$@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test test-gen install uninstall clean clean-images run-animation

test-gen: $(TEST_OBJS) $(OBJS)
	$(CC) $(TEST_OBJS) $(filter-out $(SRC_DIR)/main.o,$(OBJS)) -o $(BIN_DIR)/test_runner $(LDLIBS)

test: test-gen
	bash $(SCRIPT_DIR)/run_tests

install: $(BIN)
	install -Dm755 $(BIN) $(DESTDIR)$(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(BIN)

clean-images:
	rm -f data/*.ppm
	rm -f animation.mp4

clean: clean-images
	rm -f $(OBJS) $(TEST_OBJS) $(BIN_DIR)/$(BIN) $(BIN_DIR)/scratch $(BIN_DIR)/test_runner

scratch:
	$(CC) $(CFLAGS) $(SRC_DIR)/scratch.c -o $(BIN_DIR)/scratch $(LDLIBS)
	$(BIN_DIR)/scratch
