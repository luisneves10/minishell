# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 14:19:16 by luibarbo          #+#    #+#              #
#    Updated: 2024/09/13 14:20:24 by luibarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#	GENERAL                                                                    #
# ============================================================================ #

NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -rf

INCLUDE	= -Iinclude/
SRC_DIR	= src/
OBJ_DIR = obj/

SRC_FILES	= main.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ			= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# ============================================================================ #
#	COLORS                                                                     #
# ============================================================================ #

CLR_RMV	= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
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
	@ echo "Compilation of ${YELLOW}$(NAME) ${CLR_RMV}..."
	@ $(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(NAME)
	@ echo "$(GREEN)$(NAME) created!${CLR_RMV}"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@ $(RM) $(OBJ_DIR)
	@ echo "$(RED)Deleting $(CLR_RMV)object files"

fclean: clean
	@ $(RM) $(NAME)
	@ echo "$(RED)Deleting $(CLR_RMV)binary"

re: fclean all

.PHONY: all clean fclean re
