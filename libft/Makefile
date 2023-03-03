# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lizhang <lizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/18 21:21:47 by lizhang       #+#    #+#                  #
#    Updated: 2023/01/15 15:59:51 by hwang         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f

SRC			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
			  ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
			  ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
			  ft_strchr.c ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c\
			  ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
			  ft_strjoin.c ft_strtrim.c ft_split.c ft_space_split.c ft_itoa.c ft_strmapi.c \
			  ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			  ft_putnbr_fd.c
BSRC		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
			  ft_lstiter.c ft_lstmap.c
OBJ			= $(SRC:.c=.o)
BOBJ		= $(BSRC:.c=.o)

ifdef WITBON
COBJ		= $(OBJ) $(BOBJ)
else
COBJ		= $(OBJ)
endif

all:		$(NAME)

$(NAME):	$(COBJ)
				ar -rcs $(NAME) $(COBJ)

bonus:
				$(MAKE) WITBON=1 all

clean:
				$(RM) $(COBJ)

fclean:		clean 
				$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		make all clean fclean re so bonus
