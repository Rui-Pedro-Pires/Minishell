NAME = minishell

LIBFT = ./includes/Libft/libft.a

RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RES = \033[0m

CC = cc

CFLAGS = -Werror -Wall -Wextra -g 

LFLAG = -lreadline

RM = rm -rf

SDIR := src
ODIR := obj

SOURCES := main.c \
			list_utils.c\
			error_handler.c\
			free_memory.c\
			cmd_utils.c\
			org_list_utils.c\
			input_parser1.c\
			input_parser2.c\
			
OBJECTS := $(patsubst %.c,$(ODIR)/%.o,$(SOURCES))


all : ${NAME}

${NAME} : ${OBJECTS} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} -o ${NAME} $(LFLAG)
	@echo "\n$(GRN)➾ Minishell created$(RES)"

$(LIBFT):
	@make bonus -C ./includes/Libft/ -s
	@echo "${GRN}➾ $@ created ${RES}"

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "${GRN}➾ $@ created ${RES}"

$(ODIR):
	@mkdir -p $@	

clean :
	@${RM} ${OBJECTS}
	@${RM} ${ODIR}
	@echo "${RED}➾ Minishell objects deleted${RES}"
	@make clean -C./includes/Libft/ -s

fclean : clean
	@${RM} ${NAME}
	@echo "${RED}➾ Minishell deleted${RES}"
	@make fclean -C ./includes/Libft/ -s

re : fclean all

.PHONY: bonus
