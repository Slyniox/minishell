# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 09:30:42 by soelalou          #+#    #+#              #
#    Updated: 2024/02/17 16:01:01 by soelalou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME		= minishell
LIBFT		= libft/libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Iinc -g3
FLAGS		= -lreadline
RM			= rm -rf

SRCS_DIR	= src
OBJS_DIR	= bin

SRCS		= $(shell find $(SRCS_DIR) -type f -name '*.c')
OBJS		= $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# **************************************************************************** #
# COLORS

GREEN		= \033[0;32m
GREY		= \033[1;30m
PURPLE		= \033[0;35m
BLUE		= \033[0;94m
CYAN		= \033[0;36m
PINK		= \033[1;35m
RED			= \033[0;31m
END_COLOR	= \033[0;39m


# **************************************************************************** #
# RULES

all: dependencies $(NAME) utils

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(FLAGS)
	@echo "$(GREEN)[Success]$(END_COLOR) Minishell is ready !"

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

dependencies:
	@make -s -C libft

utils:
	@touch input
	@echo salut > input
	@echo ca va >> input
	@echo ou quoi >> input
	@touch input2
	@echo c\'est soso > input2
	@echo qui a fait >> input2
	@echo ce systeme >> input2
	@mkdir -p assets

clean:
	@$(RM) $(OBJS_DIR)
	@make clean -s -C libft
	@echo "$(GREY)[Clean]$(END_COLOR) Objects have been deleted"

fclean: clean
	@$(RM) $(OBJS_DIR) $(NAME) input input2 output a.out assets
	@make fclean -s -C libft
	@echo "$(GREY)[Clean]$(END_COLOR) $(NAME) and executables have been deleted"

re: fclean all
	@echo "$(PURPLE)[Rebuild]$(END_COLOR) Done."

.PHONY: all clean fclean re