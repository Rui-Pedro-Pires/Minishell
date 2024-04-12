NAME = minishell

NAME_BONUS = minishell_bonus

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

VG	=	valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup --track-origins=yes --log-file=leaks.log

LFLAG = -lreadline

RM = rm -rf

SDIR := src
ODIR := obj

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
			
OBJECTS := $(patsubst %.c,$(ODIR)/%.o,$(SOURCES))

all : ${NAME}

bonus : ${NAME_BONUS}

${NAME} : ${OBJECTS} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} -o ${NAME} $(LFLAG)
	@echo "\n$(GRN)➾ Minishell created$(RES)"

${NAME_BONUS} : ${OBJECTS} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} -o ${NAME_BONUS} $(LFLAG)
	@echo "\n$(GRN)➾ minishell_bonus created$(RES)"

$(LIBFT):
	@make bonus -C ./includes/Libft/ -s
	@echo "${GRN}➾ $@ created ${RES}"

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "${GRN}➾ $@ created ${RES}"

$(ODIR):
	@mkdir -p $@	
#######################
# TESTER PARA O JORGE #
#######################
KELHO_TESTER = kelho_tester

KELHO_TESTER_C = $(SDIR)/builtins/echo/echo.c
KELHO_TESTER_O = $(patsubst %.c,$(ODIR)/%.o,$(KELHO_TESTER_C))

k : $(KELHO_TESTER_O) ${LIBFT}
	@${CC} ${CFLAGS} $(KELHO_TESTER_O) ${LIBFT} -o $(KELHO_TESTER) $(LFLAG)
	@echo "\n$(GRN)➾ $(KELHO_TESTER) created$(RES)"

$(KELHO_TESTER_O): $(KELHO_TESTER_C) | $(ODIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "${GRN}➾ $@ created ${RES}"

kclean :
	@${RM} $(KELHO_TESTER)
	@echo "${RED}➾ kelhotester deleted${RES}"
	@${RM} $(KELHO_TESTER_O)
	@echo "${RED}➾ kelhotester.o deleted${RES}"

#######################
# TESTER PARA O JORGE #
#######################
clean :
	@${RM} ${OBJECTS}
	@${RM} ${ODIR}
	@echo "${RED}➾ Minishell objects deleted${RES}"
	@make clean -C./includes/Libft/ -s

fclean : clean
	@${RM} ${NAME}
	@echo "${RED}➾ Minishell deleted${RES}"
	@${RM} sup
	@echo "${RED}➾ Sup File deleted${RES}"
	@${RM} leaks.log
	@echo "${RED}➾ Leaks.log deleted${RES}"
	@make fclean -C ./includes/Libft/ -s

re : fclean all

debug: all sup_file
	@echo "$(GREEN)Minishell compiled in debug mode!$(DEF_COLOR)"

leaks: ./minishell
	@if [ -f leaks.log ]; then mv leaks.log leaks-old.log; fi
	$(VG) ./minishell

gdb: re
	gdb --tui $(NAME)

.PHONY: bonus

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
