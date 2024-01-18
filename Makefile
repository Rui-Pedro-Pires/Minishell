SRC = ./src/main.c

OBJ = $(SRC:.c=.o)

INCLUDE = ./includes/minishell.h

CFLAGS = -Wall -Werror -Wextra

LIBFT = ./includes/Libft/libft.a

CC = cc

RM = rm -f

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -I INCLUDE -lreadline

$(LIBFT):
	make -C ./include/Libft -s

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all