# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lizhang <lizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/26 12:49:53 by lizhang       #+#    #+#                  #
#    Updated: 2023/02/19 15:36:08 by lizhang       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra #-fsanitize=address
RM			= rm -f
INCLUDE		= -lreadline -Ilibft -L /Users/$(USER)/.brew/opt/readline/lib
USER		= lizhang

SRCS		= built_ins.c built_ins_variable.c built_ins_sort.c\
			built_ins_unset.c built_ins_echo.c built_ins_home.c\
			built_ins_cd.c built_ins_export_var.c built_ins_export_print.c \
			built_ins_export_rm.c built_ins_cd_utils.c built_ins_exit.c\
			lexer.c lexer_utils.c lexer_utils2.c shlvl_increment.c append.c\
			exe_cmd.c exe_redir_rm.c exe_redir_get.c exe_syntax_error.c\
			execute.c execute2.c execute3.c execute4.c pipe_functions.c\
			heredoc.c expansions.c expansions2.c executable.c \
			main.c error.c clear.c clear2.c signal.c

OBJ			= $(SRCS:.c=.o)

all:		$(NAME)
$(NAME):	$(OBJ)
				$(MAKE) bonus -C libft
				$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) libft/libft.a   \
				-o $(NAME)

%.o:%.c
				$(CC) -c $(CFLAGS) -o $@ $<

clean:
				$(RM) $(OBJ) && cd libft && $(MAKE) WITBON=1 clean

fclean:		clean
				$(RM) $(NAME) && cd libft && $(MAKE) WITBON=1 fclean

re:			fclean $(NAME)

.PHONY:		make all clean fclean re bonus