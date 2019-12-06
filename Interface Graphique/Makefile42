# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: main 

main: main.o grayscale.o pixel_operations.o decoupage.o
grayscale: pixel_operations.o grayscale.o
decoupage: decoupage.o 

grayscale.o: pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} grayscale
	${RM} main
	${RM} decoupage

# END
