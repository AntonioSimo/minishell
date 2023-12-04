# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimone <asimone@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 14:29:32 by asimone           #+#    #+#              #
#    Updated: 2023/12/04 13:51:06 by asimone          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL :=  /bin/bash

NAME := minishell
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := lib/Libft
LIBFT := $(LIBFT_DIR)/libft.a
HEAD := ./include/minishell.h
SOURCES := 	$(SRC_DIR)/builtin.c \
			$(SRC_DIR)/cd.c \
			$(SRC_DIR)/commands_utils.c \
			$(SRC_DIR)/dollar_expansion.c \
			$(SRC_DIR)/echo.c \
			$(SRC_DIR)/env.c \
			$(SRC_DIR)/env2.c \
			$(SRC_DIR)/env3.c \
			$(SRC_DIR)/error.c \
			$(SRC_DIR)/execution.c \
			$(SRC_DIR)/execution2.c \
			$(SRC_DIR)/exit.c \
			$(SRC_DIR)/expander_checkers.c \
			$(SRC_DIR)/expander_utils.c \
			$(SRC_DIR)/expander.c \
			$(SRC_DIR)/export_utils.c \
			$(SRC_DIR)/export.c \
			$(SRC_DIR)/lexer.c \
			$(SRC_DIR)/lexer2.c \
			$(SRC_DIR)/lexer3.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/parsing2.c \
			$(SRC_DIR)/parsing3.c \
			$(SRC_DIR)/pwd.c \
			$(SRC_DIR)/quotes.c \
			$(SRC_DIR)/redirections_utils.c \
			$(SRC_DIR)/redirections_utils2.c \
			$(SRC_DIR)/redirections_utils3.c \
			$(SRC_DIR)/redirections.c \
			$(SRC_DIR)/signals.c \
			$(SRC_DIR)/status_exe.c \
			$(SRC_DIR)/tilde.c \
			$(SRC_DIR)/tokenization.c \
			$(SRC_DIR)/tokens_symbols.c \
			$(SRC_DIR)/tokens_utils.c \
			$(SRC_DIR)/tokens_utils2.c \
			$(SRC_DIR)/tokens_utils3.c \
			$(SRC_DIR)/unset.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/utils2.c \
			$(SRC_DIR)/utils3.c \

OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
LFLAGS := -lreadline -lhistory
IFLAGS := -Iinclude -I$(LIBFT_DIR)/include
 
ifeq ($(shell uname -s),Darwin)
	IFLAGS := $(IFLAGS) -I$(shell brew --prefix readline)/include
	LFLAGS := $(LFLAGS) -L$(shell brew --prefix readline)/lib
	IFLAGS := $(IFLAGS) -I .brew/opt/readline/include
	LFLAGS := $(LFLAGS) -L /opt/homebrew/Cellar/readline/8.1.2/lib -lreadline
endif

GREEN = \x1b[32;01m
RED = \033[91m
YELLOW = \033[33m
BOLD = \033[1m
RESET = \x1b[0m
RM = /bin/rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) --quiet

$(NAME): $(LIBFT) $(HEAD) $(OBJ_DIR) $(OBJECTS) $(SOURCES)
	@$(CC) $(CFLAGS) $(IFLAGS) $(SOURCES) $(LIBFT) $(LFLAGS) -o $(NAME)
	@printf "$(GREEN) $(BOLD)======= Created program $(NAME) ======= $(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(HEADERS) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(YELLOW) $(BOLD)Compiling... $(RESET) $(notdir $<)\n"

clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(RM) -rf lib/Libft/obj_files
	@printf "$(RED) $(BOLD) Deleting objects... $(RESET)\n"

fclean: clean
	@$(RM) -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@printf "$(RED) $(BOLD) Deleting $(NAME)... $(RESET)\n"

re: fclean all

run:
	make && ./minishell

.PHONY: all clean fclean re
