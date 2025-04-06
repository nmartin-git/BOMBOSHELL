# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 15:41:03 by nmartin           #+#    #+#              #
#    Updated: 2025/04/06 14:09:07 by nmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW = \033[33m
GREEN = \033[32m
PURPLE = \033[35m
BLUE = \033[34m
RESET = \033[0m

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -MMD -MP
NAME = bomboshell
MINISHELL_PATH = ./minishell/
MINISHELL_FILES = bomboshell.c
MINISHELL := $(addprefix $(MINISHELL_PATH), $(MINISHELL_FILES))
PARSING_PATH = ./parsing/
PARSING_FILES = parsing.c tokenisation.c input_set.c parsing_utils.c quotes_utils.c
PARSING := $(addprefix $(PARSING_PATH), $(PARSING_FILES))
EXEC_PATH = ./exec/
EXEC_FILES = exec.c exec_tokenisation.c exec_utils.c
EXEC := $(addprefix $(EXEC_PATH), $(EXEC_FILES))
BUILT_PATH = ./built-ins/
BUILT_FILES = #built-ins.c built_utils.c cmd.c built_cd.c built_echo.c built_env.c built_exit.c built_export.c built_pwd.c built_unset.c
BUILT := $(addprefix $(BUILT_PATH), $(BUILT_FILES))
OBJ_PATH = ./objs/
OBJ := $(addprefix $(OBJ_PATH), $(MINISHELL_FILES:.c=.o)) $(addprefix $(OBJ_PATH), $(PARSING_FILES:.c=.o)) $(addprefix $(OBJ_PATH), $(EXEC_FILES:.c=.o)) $(addprefix $(OBJ_PATH), $(BUILT_FILES:.c=.o))
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
	@printf "$(BLUE)Compiling $(NAME): [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_PATH)%.o : $(PARSING_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME) parsing: [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_PATH)%.o : $(EXEC_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME) exec: [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_PATH)%.o : $(BUILT_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME) built-ins: [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_BNS_PATH)%.o : $(SRC_BNS_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME) bonus: [$<] $(RESET)"
	@mkdir -p $(OBJ_BNS_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(LIBFT) :
	@make -C $(LIBFT_PATH) --no-print-directory

clean :
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -rf $(OBJ_PATH)
	@printf "$(YELLOW)Cleaned successfully\n$(RESET)"

fclean :
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -rf $(OBJ_PATH)
	@rm -rf $(NAME)
	@printf "\r\033[K$(YELLOW)Full cleaned successfully\n$(RESET)"

re : fclean all

#commands perso

exec : fclean all
	@make clean --no-print-directory

.PHONY : all clean fclean re

-include $(DEPS)