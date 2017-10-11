# The simplest makefile:
CC:=gcc
CFLAGS:=-Wall -std=c99

# on the left is the name of the program.
# on the right are the input files it depends on.
class5: main.c city.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: run
run: class5
	./$^

.PHONY: clean
clean:
	rm -rf class5

# We want to compile and run by default.
.DEFAULT_GOAL:=run
