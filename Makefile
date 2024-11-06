# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 14:19:16 by luibarbo          #+#    #+#              #
#    Updated: 2024/11/06 16:16:26 by daduarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#	GENERAL                                                                    #
# ============================================================================ #

NAME	= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LIBFLAGS	= -lreadline
RM			= rm -rf

INCLUDE		= -Iinclude/
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= libft/
LIBFT		= libft/libft.a

LEAKS_LOG		= ./leaks.log
READLINE_SUPP	= readline.supp
VALGRINDFLAGS	= -s --suppressions=$(READLINE_SUPP) \
				  --tool=memcheck --leak-check=full \
				  --show-leak-kinds=all --track-origins=yes \
				  --track-fds=yes --show-below-main=no
VALGRINDFLAGS2	= --log-file=$(LEAKS_LOG)

SRC_FILES	= 0_main.c \
			  1_init_minishell.c 1_constructors.c 1_parse_func.c \
			  1_parse_utils.c 1_parse_utils2.c 1_env_utils.c 1_syntax_check.c \
			  1_clean_token.c 1_expansions.c \
			  2_executor.c 2_executor2.c 2_pipe_exec.c 2_redirs_exec.c \
			  2_heredoc.c 2_heredoc_utils.c \
			  3_signals.c \
			  4_builtins.c 4_echo.c 4_pwd.c 4_export.c 4_export2.c \
			  4_export3.c 4_unset.c 4_env.c 4_exit.c 4_utils.c 4_cd.c \
			  5_free_functions.c \
			  6_error.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ			= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# ============================================================================ #
#	COLORS                                                                     #
# ============================================================================ #

CLR_RMV	= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
R_GREEN	= \033[0;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
CYAN 	= \033[1;36m

# ============================================================================ #
#	RULES                                                                      #
# ============================================================================ #

all: $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	@ make -C $(LIBFT_DIR) -s
	@ echo "Compilating ${YELLOW}$(NAME) ${CLR_RMV}..."
	@ $(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(NAME) $(LIBFLAGS) $(LIBFT)
	@ echo "${GREEN}           _       _     _          _ _"
	@ echo " _ __ ___ (_)_ __ (_)___| |__   ___| | |"
	@ echo "| '_ \` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |"
	@ echo "| | | | | | | | | | \\__ \\ | | |  __/ | |"
	@ echo "|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|"
	@ echo "${R_GREEN}        by ${GREEN}daduarte ${R_GREEN}& ${GREEN}luibarbo"
	@ echo "${CLR_RMV}"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@ make clean -C $(LIBFT_DIR) -s
	@ $(RM) $(OBJ_DIR)
	@ echo "$(RED)Deleting $(CLR_RMV)object files"

fclean: clean
	@ make fclean -C $(LIBFT_DIR) -s
	@ $(RM) $(NAME)
	@ echo "$(RED)Deleting $(CLR_RMV)binary"

re: fclean all

leaks: re
	valgrind $(VALGRINDFLAGS) $(VALGRINDFLAGS2) ./$(NAME)
	cat $(LEAKS_LOG)

le: re
	valgrind $(VALGRINDFLAGS) ./$(NAME)

.PHONY: all clean fclean re leaks le
