# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#              #
#    Updated: 2024/05/31 22:47:07 by nvillalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#···COLOURS·····#
BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
PUR			= \033[0;35m
YLW			= \033[0;33m
RST			= \033[0m
END			= \e[0m

#···NAME········#
NAME = pipex

#···PATH········#
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/

#···COMPILER····#
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
CFLAGS += -I $(INC_PATH) -I $(LIBFT_DIR) -I $(SRC_PATH)

#···SRCS········#
SRC = main.c utils.c get_path.c pipex.c

INC = pipex.h

OBJ_NAME = $(SRC:%.c=%.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))


#···RM··········#
RM = rm -rf

#···LIBFT·······#
LIBFT_DIR = libft
LDFLAGS = -L $(LIBFT_DIR)
LDLIBS = -lft

#···RULES······#
.PHONY: all re clean fclean debug

all: $(NAME)
	@echo "\033[2K\r${GRN}[CREATED]\033[0m $(NAME)\n"

$(NAME): $(OBJ)
	make -sC $(LIBFT_DIR)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	@echo "\033[2K\r${PUR}[COMPILING LIBFT]${RST}'$<'\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC_PATH)/$(INC)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[2K\r${BLU}[COMPILING SOURCES]${RST}'$<'\n"
	
debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

clean:
	make fclean -sC $(LIBFT_DIR)
	$(RM) $(OBJ_PATH)
	@echo "\033[2K\r${RED}[CLEANED]\033[0m $(NAME)\n"

fclean: clean
	$(RM) $(NAME)
	@echo "\033[2K\r${RED}[FCLEANED]\033[0m $(NAME)\n"
	
re: fclean all