# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bat <bat@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 17:02:03 by bat               #+#    #+#              #
#    Updated: 2024/01/22 00:19:58 by bat              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FINAL EXECUTABLE NAME
#NAME = minishell

# DIRECTORIES
#PARSING_FOLDER = 		parsing
#EXECUTING_FOLDER = 		execution
#SIGNALS_FOLDER = 		signals
#LINKED_LISTS_FOLDER = 	linked_lists
#HEADER_DIRECTORY := 	./includes
#SRCS_DIRECTORY := 		./srcs
#LIBFT_FOLDER =			$(SRCS_DIRECTORY)/libft
#LIBFT_HEADER = 			$(SRCS_DIRECTORY)/libft/libft.h
#LIBFT_ARCHIVES = 		$(SRCS_DIRECTORY)/libft/libft.a


# ALL FILES.C
#MAIN_FILE = main.c

#MINISHELL_FILES = 		minishell.c

#PARSING_FILES = 		parser.c \
						error.c

#EXECUTING_FILES = 		builtin.c \
						executor.c

#BUILTINS_FILES = 		cd.c \
						echo.c \
						exit.c \
						export.c \
						export_utils.c \
						pwd.c \
						unset.c

#SIGNALS_FILES = 		signals.c \

#LINKED_LISTS_FILES = 	1_linkedList.c \
						2_linkedList.c \
						3_linkedList.c
						
#INCLUDES_FILES = 		minishell.h

# GLOBAL VARIABLES
#MAKE = make -C
#CC = gcc -g3 -fsanitize=address
#CFLAGS = -Wall -Wextra -Werror -O3 -g -Iincludes
#SRCS = $(MAIN_FILE) \
$(addprefix $(SRCS_DIRECTORY)/builtins/, $(BUILTINS_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/minishell/, $(MINISHELL_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/parsing/, $(PARSING_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/execution/, $(EXECUTING_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/linked_lists/, $(LINKED_LISTS_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/signals/, $(SIGNALS_FILES))
#OBJS = $(SRCS:.c=.o)
#RM = rm -f

#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@
	
#all: $(NAME)

#$(NAME): $(OBJS) libft/libft.a
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./srcs/libft -lft -lreadline 
#libft/libft.a:
#	@make -C $(LIBFT_FOLDER)

#$(SRCS_DIRECTORY)/%.o: $(SRCS_DIRECTORY)/%.c
#	$(CC) $(CFLAGS) -c $< -o $@

#clean:
#	$(RM) $(OBJS)
#	@make -C $(LIBFT_FOLDER) clean
	
#fclean: clean
#	${RM} $(NAME)
#	${RM} $(LIBFT_ARCHIVES)
#	@make -C $(LIBFT_FOLDER) fclean

#re: fclean all

#.PHONY:	all  clean fclean re*/

# FINAL EXECUTABLE NAME
NAME = minishell

# DIRECTORIES
HEADER_DIRECTORY := ./includes
SRCS_DIRECTORY := ./srcs
LIBFT_FOLDER := $(SRCS_DIRECTORY)/libft

# ALL FILES.C
MAIN_FILE := main.c

# MINISHELL_FILES := $(wildcard $(SRCS_DIRECTORY)/minishell/*.c)
PARSING_FILES := $(wildcard $(SRCS_DIRECTORY)/parsing/*.c)
EXECUTING_FILES := $(wildcard $(SRCS_DIRECTORY)/execution/*.c)
BUILTIN_FILES := $(wildcard $(SRCS_DIRECTORY)/builtin/*.c)
LINKED_LIST_FILES := $(wildcard $(SRCS_DIRECTORY)/linked_list/*.c)

INCLUDES_FILES := $(wildcard $(HEADER_DIRECTORY)/*.h)

# GLOBAL VARIABLES
CC := gcc -g3 -fsanitize=address
CFLAGS := -Wall -Wextra -Werror -O3 -g -I$(HEADER_DIRECTORY)
LDFLAGS := -L/usr/local/opt/readline/lib
CPPFLAGS := -I/usr/local/opt/readline/include
#LDFLAGS := -L/opt/homebrew/opt/readline/lib
#CPPFLAGS := -I/opt/homebrew/opt/readline/include
SRCS := $(MAIN_FILE) $(MINISHELL_FILES) $(PARSING_FILES) $(EXECUTING_FILES) $(BUILTIN_FILES) $(LINKED_LIST_FILES)
OBJS := $(SRCS:.c=.o)
RM := rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) -L./srcs/libft -lft $(LDFLAGS) -lreadline -o $(NAME)

libft/libft.a:
	@make -C $(LIBFT_FOLDER)

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT_FOLDER) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_ARCHIVES)
	@make -C $(LIBFT_FOLDER) fclean

re: fclean all

.PHONY: all clean fclean re
