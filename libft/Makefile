# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 16:15:41 by ejones            #+#    #+#              #
#    Updated: 2026/01/06 14:59:32 by ejones           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILD_DIR ?= ./build
SRC_DIR = ./src
INC_DIR = ./header

LIBFT = ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_strchr.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

PRINTF = ft_printf.c \
	ft_printf_putadress_fd.c ft_printf_putchar_fd.c ft_printf_putnbr_fd.c \
	ft_printf_putnbrbase_fd.c ft_printf_putstr_fd.c ft_printf_uiputnbr_fd.c

LIBFT_OBJ = $(addprefix $(BUILD_DIR)/, $(LIBFT:.c=.o))
PRINTF_OBJ = $(addprefix $(BUILD_DIR)/, $(PRINTF:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -MMD -MP

NAME = libft.a

all: $(NAME)
	@bash ./PrintRules/make
	@ls

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT_OBJ) $(PRINTF_OBJ)
	@ar rcs $(NAME) $(LIBFT_OBJ) $(PRINTF_OBJ)
	@echo "The Object files have been Compiled"
	@echo "The Library has been made!!!!!!"

# Removes all *.o files compiled from source and bonus
clean:
	@rm -rf $(BUILD_DIR);
	@bash ./PrintRules/clean
	@echo "Objects were removed Succesfully!!!!"

# Does clean and removes libft.a
fclean: clean
	@rm -f $(NAME)
	@rm -f a.out
	@bash ./PrintRules/fclean
	@echo "The Library was Succesfully Removed!!!!"

# Does fclean and then recompiles everything
re:  fclean print_re $(NAME)

print_re:
	@bash ./PrintRules/re
	@ls

# Declaration of PHONY intructions
.PHONY: all clean fclean re bonus print_re

-include $(LIBFT_OBJ:.o=.d)
