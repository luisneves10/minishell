# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 11:54:05 by luibarbo          #+#    #+#              #
#    Updated: 2024/06/19 09:56:16 by luibarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE	=	-I include
SRC_DIR	=	src/
OBJ_DIR	=	obj/
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
AR		=	ar rcs
RM		=	rm -rf

# COLORS
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
B_GREEN		=	\033[1;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m


SRC_FILES =	ft_isalpha ft_isdigit ft_isalnum ft_isascii \
	ft_isprint ft_strlen ft_memset ft_bzero ft_memcpy \
	ft_memmove ft_strlcpy ft_strlcat ft_toupper ft_tolower \
	ft_strchr ft_strrchr ft_strncmp ft_memchr ft_memcmp \
	ft_strnstr ft_atoi ft_calloc ft_strdup ft_substr \
	ft_strjoin ft_strtrim ft_putchar_fd ft_putstr_fd \
	ft_putendl_fd ft_split ft_itoa ft_putnbr_fd ft_strmapi \
	ft_striteri get_next_line get_next_line_utils \
	ft_printf ft_putchar_pf ft_putstr_pf ft_putnbr_pf \
	ft_putnbr_unsigned_pf ft_puthexa_pf ft_putpointer_pf \


SRC	=	${addprefix ${SRC_DIR}, ${addsuffix .c, ${SRC_FILES}}}

OBJ	=	${SRC:${SRC_DIR}%.c=$(OBJ_DIR)%.o}

${OBJ_DIR}%.o : ${SRC_DIR}%.c
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${NAME} : ${OBJ_DIR} ${OBJ}
	@${AR} ${NAME} ${OBJ}
	@echo "[$(CYAN)libft$(DEF_COLOR)] ${NAME} created successfully!"

${OBJ_DIR} :
	@mkdir -p ${OBJ_DIR}

all : ${NAME}

clean :
	@${RM} ${OBJ_DIR}
	@echo "[$(CYAN)libft$(DEF_COLOR)] .o files cleaned!"

fclean : clean
	@${RM} ${NAME}
	@echo "[$(CYAN)libft$(DEF_COLOR)] ${NAME} cleaned!"

re : fclean all
	@echo "[$(CYAN)libft$(DEF_COLOR)] Cleaned and rebuilt successfully!"

.PHONY : all clean fclean re
