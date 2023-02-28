# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 14:57:54 by lreille           #+#    #+#              #
#    Updated: 2023/02/26 17:36:12 by lreille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address 
RM = rm -f
LINK = -L$(HOME)/homebrew/opt/readline/lib -lreadline
COMPILE = -I/$(HOME)/homebrew/opt/readlin/include
OBJ = $(SOURCES:.c=.o)

.SILENT:$(OBJ)

SOURCES =	sources/exec_binary.c		\
		sources/ft_builtins.c		\
		sources/ft_builtins_utils.c	\
		sources/ft_check.c		\
		sources/ft_check2.c		\
		sources/ft_echo.c		\
		sources/ft_echo_utils1.c	\
		sources/ft_error.c		\
		sources/ft_exec_bin.c		\
		sources/ft_exit.c		\
		sources/ft_export.c		\
		sources/ft_export_utils1.c	\
		sources/ft_export_utils2.c	\
		sources/ft_free_main.c		\
		sources/ft_free_redirection.c	\
		sources/ft_free_utils.c		\
		sources/ft_parse_check.c	\
		sources/ft_parse_command.c	\
		sources/ft_parse_env.c		\
		sources/ft_parse_redirection.c	\
		sources/ft_pipe_check.c		\
		sources/ft_redir_utils.c	\
		sources/ft_redirection.c	\
		sources/ft_redirectfile.c	\
		sources/ft_sig.c		\
		sources/ft_split.c		\
		sources/ft_utils1.c		\
		sources/ft_utils2.c		\
		sources/ft_utils3.c		\
		sources/ft_utils4.c		\
		sources/minishell.c		\

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LINK) $(OBJ) -o $(NAME)
%.o: %.c
	$(CC) $(FLAGS) $(COMPILE) -c $< -o $@

clean:
	@$(RM) $(OBJ)
fclean:
	@$(RM) $(NAME) $(OBJ)
re: fclean all

r: all
	@clear && ./minishell

.PHONY: all clean fclean re
