# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 12:13:46 by aboumall          #+#    #+#              #
#    Updated: 2025/01/17 01:28:48 by ayoub            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a
HEAD 	= libft.h

CC 		= cc

CFLAGS  = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj

IS_DIR  = $(SRC_DIR)/ft_is
STR_DIR = $(SRC_DIR)/str
PUT_DIR = $(SRC_DIR)/put
LST_DIR = $(SRC_DIR)/lst
MEM_DIR = $(SRC_DIR)/mem
PF_DIR  = $(SRC_DIR)/ft_printf
GNL_DIR = $(SRC_DIR)/gnl

IS_SRC  = 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c
STR_SRC = 	ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_striteri.c ft_strncmp.c \
			ft_strrchr.c ft_strnstr.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strmapi.c \
			ft_toupper.c ft_tolower.c ft_split.c ft_strtrim.c ft_atoi.c ft_itoa.c
PUT_SRC = 	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
LST_SRC =	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
MEM_SRC =	ft_bzero.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_memmove.c \
			ft_memset.c ft_calloc.c
PF_SRC  =	ft_printf.c ft_printf_utils.c flags.c
GNL_SRC =	get_next_line.c

SRC 	= 	$(addprefix $(IS_DIR)/, $(IS_SRC))		\
			$(addprefix $(STR_DIR)/, $(STR_SRC)) 	\
			$(addprefix $(PUT_DIR)/, $(PUT_SRC))	\
			$(addprefix $(LST_DIR)/, $(LST_SRC)) 	\
			$(addprefix $(MEM_DIR)/, $(MEM_SRC))	\
			$(addprefix $(PF_DIR)/, $(PF_SRC))		\
			$(addprefix $(GNL_DIR)/, $(GNL_SRC))

OBJ 	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD) Makefile | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re