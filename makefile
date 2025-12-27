# Main program
PROG := main

# Files to exclude
EXCLUDE := main.c pixmap.c

# Source code: all .c files in src except excluded ones
# SRC := ${wildcard src/*.c}  # old method
SRC := $(filter-out $(addprefix src/, $(EXCLUDE)), $(wildcard src/*.c src/*/*.c))

# Object code 
OBJ := ${SRC:.c=.o}

# flags of each type
CC = gcc 
# The last two: ❯ pkg-config --cflags xft
INCLUDES = -I/usr/include/X11 -I/usr/include/freetype2 -I/usr/include/libpng16
LIBRARIES = -lX11 -lXft -lXinerama

# Linker Flags (From object to program)
LDFLAGS := ${LIBRARIES}

# For compilation
CFLAGS := -Wall -Wextra -O2 ${INCLUDES}

# Compiles the program
all : ${PROG}

# Link the object: $@ => Each object
# This intermediatry step is used to link the libraries
${PROG} : ${OBJ}
	${CC} ${OBJ} -o $@ ${LDFLAGS}

# Compilation of source code to object files
# $< => only one program 
%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf ${OBJ} ${PROG}

.PHONY: all clean
