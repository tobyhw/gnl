NAME	= gnl
SRC		= main.c get_next_line.c
OBJ		= $(SRC:.c=.o)
INC		= get_next_line.h
CC		= gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

gnl_%: gnl_%.o main.o
	$(CC) -o $@ $^

%.o: %.c $(INC)
	$(CC) -c $< -o $@
