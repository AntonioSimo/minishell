# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimone <asimone@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 14:58:37 by asimone           #+#    #+#              #
#    Updated: 2023/12/04 13:28:00 by asimone          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
HEADERFILES := libft.h
SRC =	src/ft_atoi.c \
		src/ft_bzero.c \
		src/ft_calloc.c \
		src/ft_free.c \
		src/ft_isalnum.c \
		src/ft_isalpha.c \
		src/ft_isascii.c \
		src/ft_isdigit.c \
		src/ft_isprint.c \
		src/ft_itoa.c \
		src/ft_lstadd_back.c \
		src/ft_lstadd_front.c \
		src/ft_lstclear.c \
		src/ft_lstiter.c \
		src/ft_lstdelone.c \
		src/ft_lstlast.c \
		src/ft_lstmap.c \
		src/ft_lstnew.c \
		src/ft_lstsize.c \
		src/ft_memchr.c \
		src/ft_memcmp.c \
		src/ft_memcpy.c \
		src/ft_memmove.c \
		src/ft_memset.c \
		src/ft_printf.c \
		src/ft_printf_utils.c \
		src/ft_putchar_fd.c \
		src/ft_putnbr_fd.c \
		src/ft_putendl_fd.c \
		src/ft_putstr_fd.c \
		src/ft_split.c \
		src/ft_strdup.c \
		src/ft_strchr.c \
		src/ft_striteri.c \
		src/ft_strjoin.c \
		src/ft_strlcat.c \
		src/ft_strlcpy.c \
		src/ft_strlen.c \
		src/ft_strmapi.c \
		src/ft_strncmp.c \
		src/ft_strnstr.c \
		src/ft_strrchr.c \
		src/ft_strtrim.c \
		src/ft_substr.c \
		src/ft_tolower.c \
		src/ft_toupper.c \
		src/get_next_line.c \
		src/ft_free_strjoin.c

SRC_DIR = src
OBJ_DIR := obj_files
OBJ := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC:.c=.o))

GREEN = \x1b[32;01m
RED = \033[91m
YELLOW = \033[33m
BOLD = \033[1m
RESET = \033[0m
RM = /bin/rm -f

AR = ar
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -rcs
RM := /bin/rm -f

all : $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(AR) $(LFLAGS) $(NAME) $(OBJ)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -Iinclude $(CFLAGS) -c $^ -o $@
	@printf "$(YELLOW) $(BOLD)Compiling... $(RESET) $(notdir $<)\n"
		
clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(RED) $(BOLD) Deleting Libft... $(RESET)\n"

fclean: clean
	@$(RM) -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
