# Makefile

CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3 -Wextra -std=c99 -O3
LDLIBS = `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl` -lSDL_image

EXE = test main 50shades

all: $(EXE)main 

main: main.o grayscale.o pixel_operations.o decoupage.o
grayscale: pixel_operations.o grayscale.o
decoupage: decoupage.o 

$(foreach f, $(EXE), $(eval $(f):))

.PHONY: clean

clean:
	${RM} $(EXE)
	${RM} *.o
	${RM} *.d
	${RM} grayscale
	${RM} main
	${RM} decoupage

# END