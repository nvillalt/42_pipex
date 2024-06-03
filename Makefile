# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 16:00:38 by nvillalt          #+#    #+#              #
#    Updated: 2024/06/03 16:06:59 by nvillalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

CFLAGS = -Wall -Wextra -Werror

INCLUDES = inc/pipex.h

RM = rm -f

SRC = src/get_path.c \
		src/main.c \
		src/pipex.c \
		src/utils.c

OBJS = ${SRC:.c=.o}

.PHONY = all clean fclean re debug

$(NAME): $(OBJS) $(INCLUDES)
		$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

clean:
		$(RM) $(OBJS)
		cd $(LIBFTDIR) && make clean

fclean: clean
		$(RM) $(NAME)
		cd $(LIBFTDIR) && make fclean

re: fclean all