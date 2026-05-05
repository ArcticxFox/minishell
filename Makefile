# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 14:58:30 by ejones            #+#    #+#              #
#    Updated: 2026/04/23 17:38:27 by ejones           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_DIR ?= ./obj
SRC_DIR := ./src
INC_DIR := ./header

SRC := main.c sig_handler.c token.c token_utils.c
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC := cc
CFLAGS += -Wall -Werror -Wextra -g

UTILS = libft/libft.a
NAME = minishell

all: make_msg $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS):
	@make -C libft

$(NAME): $(UTILS) $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(UTILS) -lreadline -lhistory
	@echo "\e[32m\n===================== FINISHED ======================\n\e[0m"

clean: cln_msg
	@echo "\e[33m	- removing ./obj\n\e[0m"
	make clean -C libft
	@rm -rf $(OBJ_DIR)
fclean: clean
	@echo "\e[33m	- deleting executables\n\e[0m"
	make fclean -C libft
	@rm -f $(NAME)
re: re_msg fclean all

#================================== Messages ==================================#
re_msg:
	@echo "\e[31m\n================= Re-making Project ===================\e[0m"
make_msg:
	@echo "\e[32m\n================== Making Project ===================\n\e[0m"
cln_msg:
	@echo "\e[33m\n==================== Cleaning =======================\n\e[0m"

.PHONY: all clean fclean re re_msg make_msg cln_msg
