# The simplest makefile:
CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -std=c99

# on the left is the name of the program.
# on the right are the input files it depends on.
draw: draw.c
	$(CC) $(CFLAGS) $^ -o $@
	@# The line above runs gcc with the flags defined at the top on the input files ($^) saving the output to "draw", or the target of this rule ($@)
	@# Lines that start with @ are not printed, otherwise the comments would come out when we ran make draw.

# we declare a phony target "run", which means it's not a real file or program. It's an "action".
.PHONY: run
# run only works if we've already compiled our code. We called that 'draw' in our makefile.
run: draw
	./$^

# Often we declare a phony target called clean that deletes our code. Then we can always make sure we're running the latest stuff with make clean; make
.PHONY: clean
clean:
	rm -rf draw

# We want to compile and run by default.
.DEFAULT_GOAL:=run
