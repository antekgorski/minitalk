# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 15:54:12 by agorski           #+#    #+#              #
#    Updated: 2024/07/02 23:45:44 by agorski          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CLIENT = client
SERVER = server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

# Define compiler
CC = gcc -g -Wall -Wextra -Werror -I


# Removing the files
RM = rm -f


# Define names of the executables
LIBFT = ./lib/printf/libft/libft.a
FT_PRINTF = ./lib/printf/libftprintf.a
INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/


SRC_CLIENT = $(addprefix $(SRC_DIR), $(addsuffix .c, $(CLIENT)))
SRC_SERVER = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SERVER)))
SRC_CLIENT_BONUS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(CLIENT_BONUS)))
SRC_SERVER_BONUS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SERVER_BONUS)))

OBJ_CLIENT = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(CLIENT)))
OBJ_SERVER = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SERVER)))
OBJ_CLIENT_BONUS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(CLIENT_BONUS)))
OBJ_SERVER_BONUS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SERVER_BONUS)))


start:
	@make all
	@make bonus


$(LIBFT):
	@make -C ./lib/printf/libft


$(FT_PRINTF):
	@make -C ./lib/printf


all: $(CLIENT) $(SERVER)


$(CLIENT):	$(OBJ_CLIENT) $(LIBFT) $(FT_PRINTF)
			@$(CC) $(INC_DIR) $(OBJ_CLIENT) $(LIBFT) $(FT_PRINTF) -o $(CLIENT)

$(SERVER):	$(OBJ_SERVER) $(LIBFT) $(FT_PRINTF)
			@$(CC) $(INC_DIR) $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF) -o $(SERVER)

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS):	$(OBJ_CLIENT_BONUS) $(LIBFT) $(FT_PRINTF)
					@$(CC) $(INC_DIR) $(OBJ_CLIENT_BONUS) $(LIBFT) $(FT_PRINTF) -o $(CLIENT_BONUS)

$(SERVER_BONUS):	$(OBJ_SERVER_BONUS) $(LIBFT) $(FT_PRINTF)
					@$(CC) $(INC_DIR) $(OBJ_SERVER_BONUS) $(LIBFT) $(FT_PRINTF) -o $(SERVER_BONUS)


$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(INC_DIR) -c $< -o $@

clean:
		@$(RM) -r $(OBJ_DIR) $(LIBFT) $(FT_PRINTF)
		@make clean -C ./lib/printf/libft
		@make clean -C ./lib/printf


fclean: clean
		$(RM) $(CLIENT) $(SERVER) $(SERVER_BONUS) $(CLIENT_BONUS)
		$(RM) $(LIB)


re: fclean all

# The .PHONY rule tells make that the listed targets are not files.
.PHONY: all clean fclean re