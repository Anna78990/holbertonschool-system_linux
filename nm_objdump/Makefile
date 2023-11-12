CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -g

SRC0 = hnm.c endians.c symbol_endians.c section.c symbol_print.c symbol_print2.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = hnm


.PHONY: all clean oclean flcean re

all: $(OBJ0) $(OBJ1)
	$(CC) $(OBJ0) -o $(NAME0)
clean:
	$(RM) *~ $(NAME0)

oclean:
	$(RM) $(OBJ0)

fclean: clean oclean

re: oclean all

hnm: hreadelf.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)
