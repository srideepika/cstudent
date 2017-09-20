# How to use gcc:

## Compiling a file:
    gcc stats.c -o stats
## Running the code:
    ./stats
## Try it for integral.c
## Look at the code.
    cat integral.c
## Try to compile. What's wrong?
    gcc integral.c -o integral
## Try again with the math library:
    gcc integral.c -lm -o integral
## Now run it.
    ./integral

# Investigating the phases of C compilation:

## Only run the preprocessor.
    gcc -E integral.c

## Only compile, don't assemble. (which one works?)
    gcc -S integral.c
    gcc -lm -S integral.c
### Inspect the assembly file:
    nano integral.s

## Compile and save an object file. (Which one works?)
    gcc -c integral.c
    gcc -lm -c integral.c
### Inspect the object file
    file integral.o

## Link a bunch of object files and libraries.
    gcc integral.o -lm -o integral3
### Run it!
    ./integral3

### Compile and link as a program:
We usually preprocess, compile, assemble and link all in one step. When you build bigger programs, you usually only link last.
    gcc integral.c -o integral2
    ./integral2

