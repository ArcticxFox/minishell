# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 14:58:30 by ejones            #+#    #+#              #
#    Updated: 2026/05/19 17:46:12 by ejones           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


OBJ_DIR := obj
SRC_DIR := src
INC_DIR := header

CC := cc

CFLAGS := -Wall -Wextra -Werror -g
CPPFLAGS := -I$(INC_DIR) -Ilibft/header

NAME := minishell

UTILS := libft/libft.a

#============================== SOURCES =======================================#

SRC := \
	main.c \
	lexer/token.c \
	lexer/token_utils.c \
	parser/get_cmds.c \
	parser/cmds_utils.c \
	parser/print_structs.c \
	builtin/builtin.c \
	builtin/builtin_utils.c \
	env/env_utils.c \
	signals/sig_handler.c \
	expander.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC))

OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

#============================== RULES =========================================#

all: make_msg $(NAME)

$(NAME): $(UTILS) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(UTILS) -lreadline -lhistory -o $(NAME)
	@echo "\e[32m\n===================== FINISHED ======================\n\e[0m"

$(UTILS):
	@make -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

#============================== CLEAN =========================================#

clean: cln_msg
	@make clean -C libft
	@rm -rf $(OBJ_DIR)
	@echo "\e[33m\t- removing object files\n\e[0m"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\e[33m\t- deleting executable\n\e[0m"

re: re_msg fclean all

#============================== MESSAGES ======================================#

make_msg:
	@echo "\e[32m\n================== Making Project ===================\n\e[0m"

re_msg:
	@echo "\e[31m\n================= Re-making Project =================\n\e[0m"

cln_msg:
	@echo "\e[33m\n==================== Cleaning =======================\n\e[0m"

#============================== PHONY =========================================#

.PHONY: all clean fclean re make_msg re_msg cln_msg
