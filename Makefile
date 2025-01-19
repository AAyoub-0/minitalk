# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aayoub <aayoub@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/19 17:12:33 by aayoub            #+#    #+#              #
#    Updated: 2025/01/19 19:45:49 by aayoub           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minitalk
HEAD 		= minitalk.h

CC 			= cc
CFLAGS 		= -g

SERVER_DIR 	= server
CLIENT_DIR 	= client
LIBFT_DIR 	= libft
SRC_DIR 	= src
OBJ_DIR 	= obj

SERVER_SRC 	= server.c
CLIENT_SRC 	= client.c
LIBFT_A 	= libft.a

SERVER 		= $(addprefix $(SERVER_DIR)/, $(SERVER_SRC))
CLIENT 		= $(addprefix $(CLIENT_DIR)/, $(CLIENT_SRC))
LIBFT 		= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))
SRC   		= $(addprefix $(SRC_DIR)/, $(SERVER) $(CLIENT))
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(HEAD) $(SRC) Makefile
	$(CC) $(CFLAGS) -o $(SERVER_DIR) $(SRC_DIR)/$(SERVER) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT_DIR) $(SRC_DIR)/$(CLIENT) $(LIBFT)
 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD) Makefile | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(SERVER_DIR)
	rm -f $(CLIENT_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re