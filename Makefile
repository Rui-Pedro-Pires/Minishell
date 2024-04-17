# Color variables
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RES = \033[0m

# Compiler-related variables
CC = cc
CFLAGS = -Werror -Wall -Wextra -g
LFLAG = -lreadline
VG = valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup --track-origins=yes --log-file=leaks.log

# File-related variables
NAME = minishell
NAME_BONUS = minishell_bonus
LIBFT = ./includes/Libft/libft.a
RM = rm -rf
SDIR := src
ODIR := obj

# Source files
SOURCES := main.c \
			error_handler.c\
			free_memory.c\
			str_join.c\
			search_utils.c\
			free.c\
			dir_list.c\
			signals.c\
			signals_handlers.c\
			heardoc/heardoc.c\
			heardoc/heardoc_utils.c\
			heardoc/heardoc_utils2.c\
			lists/create_list.c\
			lists/create_list_utils.c\
			lists/build_str_list.c\
			lists/trim_str_list.c\
			lists/trim_build_str_list_utils.c\
			lists/command_decider.c\
			lists/parenthesis_in_node.c\
			readline/read_line.c\
			readline/read_line_utils.c\
			readline/read_line_parser.c\
			parser/parser_utils.c\
			parser/parser_input.c\
			parser/parser_input_utils.c\
			parser/parser_signs.c\
			parser/parser_signs_utils.c\
			parser/parser_search_utils.c\
			parser/parser_diff_signs.c\
			parser/parser_parenthesis.c\
			builtins/cd_pwd/cd.c\
			builtins/cd_pwd/cd_utils.c\
			builtins/cd_pwd/pwd.c\
			builtins/envs/create_env_list.c\
			builtins/envs/free_env.c\
			builtins/envs/env.c\
			builtins/envs/export.c\
			builtins/envs/unset.c\
			builtins/envs/getenv.c\
			builtins/echo/echo.c\
			builtins/exit/exit.c\
			builtins/exit/exit_utils.c\
			expander/expander_utils.c\
			expander/expander_utils2.c\
			expander/expander.c\
			expander/expand_wildcards.c\
			expander/wildcardenz_utils.c\
			expander/wildcardenz_utils2.c\
			expander/wildcardenz_utils3.c\
			executer/executer.c\
			executer/executer_utils.c\
			executer/execve.c\
			executer/execve_utils.c\
			executer/define_in_out.c\
			executer/define_in_out_utils.c\
			executer/define_in_out_type.c\
			executer/read_stdin_heardoc_utils.c\
			executer/stdin_out_pipe_case.c\
			executer/split_ignore_quotes.c\
			executer/recursive_function.c\

# Object files
OBJECTS := $(patsubst %.c,$(ODIR)/%.o,$(SOURCES))

TOTAL_FILES := $(words $(SOURCES))
COMPILED_FILES := $(shell if [ -d "$(ODIR)" ]; then find $(ODIR) -name "*.o" | wc -l; else echo 0; fi)

# Targets
all : ${NAME}

bonus : ${NAME_BONUS}

${NAME} : ${OBJECTS} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} -o ${NAME} $(LFLAG)
	@printf "$(GRN)➾ Compilation progress: $$(echo "$(shell find $(ODIR) -name "*.o" | wc -l) $(TOTAL_FILES)" | awk '{printf "%.2f", $$1/$$2 * 100}')%%$(RES)\r"
	@echo "\n$(GRN)➾ Minishell created$(RES)"
	@printf "\n"

${NAME_BONUS} : ${OBJECTS} ${LIBFT}

	@${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} -o ${NAME_BONUS} $(LFLAG)
	@echo "\n$(GRN)➾ minishell_bonus created$(RES)"

$(LIBFT):
	@make bonus -C ./includes/Libft/ -s

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "$(GRN)➾ Compilation progress: $$(echo "$(shell find $(ODIR) -name "*.o" | wc -l) $(TOTAL_FILES)" | awk '{printf "%.2f", $$1/$$2 * 100}')%%$(RES)\r"

# Rest of your Makefile
$(ODIR):
	@printf "\n\
	 _____                                                                       _____ \n\
	( ___ )                                                                     ( ___ )\n\
	 |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | \n\
	 |   |                                                                       |   | \n\
	 |   |                                                                       |   | \n\
	 |   |  ___ ___    ___   ____   ____  ____    ___   _____ _____   ___  _____ |   | \n\
	 |   | |   |   |  /  _] /    | /    ||    \  /   \ / ___// ___/  /  _]/ ___/ |   | \n\
	 |   | | _   _ | /  [_ |   __||  o  ||  o  )|     (   \_(   \_  /  [_(   \_  |   | \n\
	 |   | |  \_/  ||    _]|  |  ||     ||     ||  O  |\__  |\__  ||    _]\__  | |   | \n\
	 |   | |   |   ||   [_ |  |_ ||  _  ||  O  ||     |/  \ |/  \ ||   [_ /  \ | |   | \n\
	 |   | |   |   ||     ||     ||  |  ||     ||     |\    |\    ||     |\    | |   | \n\
	 |   | |___|___||_____||___,_||__|__||_____| \___/  \___| \___||_____| \___| |   | \n\
	 |   |                                                                       |   | \n\
	 |   |                                                                       |   | \n\
	 |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| \n\
	(_____)                                                                     (_____)\n"
	@printf "\n"
	@printf "\n"

	@mkdir -p $@	

clean :
	@${RM} ${OBJECTS}
	@${RM} ${ODIR}
	@make clean -C./includes/Libft/ -s

fclean : clean
	@${RM} ${NAME}
	@${RM} ${NAME_BONUS}
	@echo "${RED}➾ Minishell deleted${RES}"
	@${RM} sup
	@${RM} leaks.log
	@${RM} leaks-old.log
	@make fclean -C ./includes/Libft/ -s

re : fclean all

debug: all sup_file
	@echo "$(GREEN)Minishell compiled in debug mode!$(DEF_COLOR)"

leaks: ./minishell
	@if [ -f leaks.log ]; then mv leaks.log leaks-old.log; fi
	$(VG) ./minishell

gdb: re
	gdb --tui $(NAME)

.PHONY: all bonus clean fclean re debug leaks gdb sup_file

define SUP_BODY
{
   name
   Memcheck:Leak
   fun:*alloc
   ...
   obj:*/libreadline.so.*
   ...
}
{
	leak readline
	Memcheck:Leak
	...
	fun:readline
}
{
	leak add_history
	Memcheck:Leak
	...
	fun:add_history
}
endef

sup_file:
	$(file > sup,$(SUP_BODY))
	@echo "$(MAG)Created suppression file to use with valgrind --suppressions=sup$(RES)"

header:
	@printf "\n\
	 _____                                                                       _____ \n\
	( ___ )                                                                     ( ___ )\n\
	 |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | \n\
	 |   |                                                                       |   | \n\
	 |   |                                                                       |   | \n\
	 |   |  ___ ___    ___   ____   ____  ____    ___   _____ _____   ___  _____ |   | \n\
	 |   | |   |   |  /  _] /    | /    ||    \  /   \ / ___// ___/  /  _]/ ___/ |   | \n\
	 |   | | _   _ | /  [_ |   __||  o  ||  o  )|     (   \_(   \_  /  [_(   \_  |   | \n\
	 |   | |  \_/  ||    _]|  |  ||     ||     ||  O  |\__  |\__  ||    _]\__  | |   | \n\
	 |   | |   |   ||   [_ |  |_ ||  _  ||  O  ||     |/  \ |/  \ ||   [_ /  \ | |   | \n\
	 |   | |   |   ||     ||     ||  |  ||     ||     |\    |\    ||     |\    | |   | \n\
	 |   | |___|___||_____||___,_||__|__||_____| \___/  \___| \___||_____| \___| |   | \n\
	 |   |                                                                       |   | \n\
	 |   |                                                                       |   | \n\
	 |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| \n\
	(_____)                                                                     (_____)\n"
	@printf "\n"
	@printf "\n"
