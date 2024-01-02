# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bat <bat@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/27 17:04:37 by bbessard          #+#    #+#              #
#    Updated: 2023/11/01 19:24:58 by bat              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDES    = -I includes -I $(LIBFT_DIR)/includes/

LIBFT_DIR   = libft/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O3

RM = rm -f

LDFLAGS = -L.

LDLIBS = -lft

HDDIRS = -I includes/

AR = ar rc

HEADER = libft.h

SRC = $(wildcard ft_strtok.c) \
$(wildcard *.c)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) 
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean git norminette re 
