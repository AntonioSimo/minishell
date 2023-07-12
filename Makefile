SHELL :=  /bin/bash

NAME := minishell
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := lib/Libft
LIBFT := $(LIBFT_DIR)/libft.a
HEAD := ./include/minishell.h
SOURCES := 	$(SRC_DIR)/cd.c \
			$(SRC_DIR)/lexer.c \
			$(SRC_DIR)/ls.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/pwd.c
#HEADERS := $(shell find include -type f -name '*.h')
#SOURCES = $(shell find $(SRC_DIR) -type f -name '*.c')

OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))
CC := cc
CFLAGS := -Wall -Wextra -Werror 
LFLAGS := -lreadline -lhistory
IFLAGS := -Iinclude -I$(LIBFT_DIR)/include
 
ifeq ($(shell uname -s),Darwin)
	IFLAGS := $(IFLAGS) -I$(shell brew --prefix readline)/include
	LFLAGS := $(LFLAGS) -L$(shell brew --prefix readline)/lib
#	IFLAGS := $(IFLAGS) -I .brew/opt/readline/include
#	LFLAGS := $(LFLAGS) -L /opt/homebrew/Cellar/readline/8.1.2/lib -lreadline
endif

GREEN = \x1b[32;01m
RED = \x1b[31;01m
YELLOW = \033[33;1m
BOLD = \033[1m
RESET = \x1b[0m
RM = /bin/rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) --quiet

$(NAME): $(LIBFT) $(HEAD) $(OBJ_DIR) $(OBJECTS)
	@$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) $(SOURCES) $(LIBFT) -o $(NAME)
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

.PHONY: all clean fclean re
