CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC0 = 0-hreadelf.c endians.c print.c print2.c print3.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = 0-hreadelf

SRC1 = 1-hreadelf.c endians.c section.c section2.c
OBJ1 = $(SRC1:.c=.o)
NAME1 = 1-hreadelf

SRC2 = 2-hreadelf.c endians.c print3.c program.c program2.c section.c section2.c
OBJ2 = $(SRC2:.c=.o)
NAME2 = 2-hreadelf

.PHONY: all clean oclean flcean re

all: $(NAME0) $(NAME1) $(NAME2)

0-hreadelf: hreadelf.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

1-hreadelf: hreadelf.h $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)

2-hreadelf: hreadelf.h $(OBJ2)
	$(CC) $(OBJ2) -o $(NAME2)
