# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 15:41:03 by nmartin           #+#    #+#              #
#    Updated: 2025/03/15 13:06:37 by nmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW = \033[33m
GREEN = \033[32m
PURPLE = \033[35m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
NAME = bomboshell
MINISHELL_PATH = ./minishell/
MINISHELL_FILES = bomboshell.c
MINISHELL := $(addprefix $(MINISHELL_PATH), $(MINISHELL_FILES))
PARSING_PATH = ./parsing/
PARSING_FILES = parsing.c
PARSING := $(addprefix $(PARSING_PATH), $(PARSING_FILES))
OBJ_PATH = ./objs/
OBJ := $(addprefix $(OBJ_PATH), $(MINISHELL_FILES:.c=.o)) $(addprefix $(OBJ_PATH), $(PARSING_FILES:.c=.o))
SRC_BNS_PATH = ./srcs_bonus/
SRC_BNS_FILES = 
SRC_BNS := $(addprefix $(SRC_BNS_PATH), $(SRC_BNS_FILES))
OBJ_BNS := $(addprefix $(OBJ_PATH), $(SRC_BNS_FILES:.c=.o))
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
HEADERS = -Iheaders -I$(LIBFT_PATH)
DEPS := $(OBJ:.o=.d)

all : $(NAME)

bonus : $(LIBFT) $(OBJ_BNS)
	@printf "$(BLUE)Creating $(NAME) bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_BNS) $(LIBFT) -o $(NAME)
	@printf "\r\033[K"
	@printf "$(GREEN)$(NAME) created successfully\n$(RESET)"

$(NAME) : $(LIBFT) $(OBJ)
	@printf "$(PUPLE)Creating $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@printf "\r\033[K"
	@printf "$(GREEN)$(NAME) created successfully\n$(RESET)"

$(OBJ_PATH)%.o : $(MINISHELL_PATH)%.c
	@printf "Compiling $(NAME): [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_PATH)%.o : $(PARSING_PATH)%.c
	@printf "Compiling $(NAME) parsing: [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_BNS_PATH)%.o : $(SRC_BNS_PATH)%.c
	@printf "Compiling $(NAME) bonus: [$<] $(RESET)"
	@mkdir -p $(OBJ_BNS_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(LIBFT) :
	@make -C $(LIBFT_PATH) --no-print-directory

clean :
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -rf $(OBJ_PATH)
	@printf "$(YELLOW)Cleaned successfully$(RESET)"

fclean : clean
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -rf $(NAME)
	@printf "\r\033[K$(YELLOW)Full cleaned successfully\n$(RESET)"

re : fclean all

#commands perso

exec : fclean all
	@make clean --no-print-directory

.PHONY : all clean fclean re

-include $(DEPS)