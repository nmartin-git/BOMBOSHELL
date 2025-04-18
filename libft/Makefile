# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 19:01:34 by nmartin           #+#    #+#              #
#    Updated: 2025/04/10 21:26:46 by nmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PURPLE = \033[35m
GREEN = \033[32m
RESET = \033[0m

CC = cc
FLAGS = -Wextra -Werror -Wall
NAME = libft.a
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
			ft_strncmp.c ft_strnstr.c ft_atoi.c ft_memset.c ft_bzero.c \
				ft_memcpy.c ft_memchr.c ft_memcmp.c ft_calloc.c ft_strdup.c \
					ft_strlcpy.c ft_strlcat.c ft_substr.c ft_strjoin.c ft_strtrim.c \
						ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
							ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_memmove.c								
OBJ = $(SRC:.c=.o)
SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
				ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJ_BONUS = $(SRC_BONUS:.c=.o)
SRC_PRINTF = ft_printf.c prnt_conv.c prnt_conv1.c prnt_conv2.c \
		prnt_utils.c prnt_errors.c prnt_check_bonus.c prnt_bonus_utils.c \
			prnt_b_checks.c 
OBJ_PRINTF = $(SRC_PRINTF:.c=.o)
SRC_GNL = get_next_line.c gnl_get_next_line_utils.c
OBJ_GNL = $(SRC_GNL:.c=.o)
SRC_UTILS = ft_free_tab.c ft_printf_fd.c ft_size_tab.c ft_abs.c ft_strjoin_free.c \
			ft_strndup.c ft_str_quotes.c
OBJ_UTILS = $(SRC_UTILS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(OBJ_BONUS) $(OBJ_PRINTF) $(OBJ_GNL) $(OBJ_UTILS)
	@ar -rcs $(NAME) $(OBJ) $(OBJ_BONUS) $(OBJ_PRINTF) $(OBJ_GNL) $(OBJ_UTILS)
	@echo "$(GREEN)Libft compiled successfully$(RESET)"

.c.o:
	@printf "$(PURPLE)Compiling libft: [$<]$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\r\033[K"

clean :
	@rm -rf *.o

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
