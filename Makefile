# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 14:58:30 by ejones            #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2026/06/29 13:05:17 by leonpouet        ###   ########.fr        #
=======
#    Updated: 2026/06/29 20:39:16 by ejones           ###   ########.fr        #
>>>>>>> 1e3a783 (j'ai fais la fonction de gestion d'erreur de syntax, modifier le nom de certain fichier dans le dossier parseur)
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
	lexer/token_utils2.c \
	lexer/syntax_errors.c \
	builtin/builtin.c \
	builtin/builtin_utils.c \
	builtin/builtin_next.c \
	env/env_utils.c \
	signals/sig_handler.c \
 	parser/get_cmds.c \
	parser/print_structs.c \
	parser/cmd_linked_lst.c \
	parser/redir_parser.c \
	parser/parser_utils.c \
	expander.c \
	execute/execute_utils.c \
	execute/execute_redir.c \
	execute/execute.c \
	pipe/pipe.c

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
