# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/19 17:12:33 by aayoub            #+#    #+#              #
#    Updated: 2025/02/13 14:11:38 by aboumall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minitalk
HEAD 			= minitalk.h

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror

SERVER_DIR 		= server
CLIENT_DIR 		= client
LIBFT_DIR 		= libft
SRC_DIR 		= src
OBJ_DIR 		= obj

SERVER_SRC 		= server.c
CLIENT_SRC 		= client.c client_utils.c
LIBFT_A 		= libft.a

SERVER_FILES	= $(addprefix $(SRC_DIR)/$(SERVER_DIR)/, $(SERVER_SRC))
CLIENT_FILES	= $(addprefix $(SRC_DIR)/$(CLIENT_DIR)/, $(CLIENT_SRC))

SERVER_OBJ		= $(SERVER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CLIENT_OBJ		= $(CLIENT_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT 			= $(LIBFT_DIR)/$(LIBFT_A)
SERVER_BIN 		= server
CLIENT_BIN 		= client

all: $(NAME)

$(NAME): $(LIBFT) $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_OBJ) $(LIBFT) Makefile

$(CLIENT_BIN): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_OBJ) $(LIBFT) Makefile

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(SERVER_BIN) $(CLIENT_BIN)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
