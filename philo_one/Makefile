# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/03 12:23:24 by darbib            #+#    #+#              #
#    Updated: 2021/03/18 12:49:58 by darbib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE = 		'\033[0;34m'
GREEN = 	'\033[0;32m'
LIGHTBLUE = '\033[1;34m'
RED = 		'\033[0;31m'
YELLOW = 	'\033[1;33m'
ORANGE = 	'\033[0;33m'
MAGENTA = 	'\033[0;35m'
RESET = 	'\033[0m'

NAME = philo_one
CFLAGS= -Wall -Wextra -Werror  
CC = clang
LIBS = -pthread

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SANITIZE), 1)
	CFLAGS += -fsanitize=address
endif

# ------------------------------------------------------------------------------

OBJ_DIR = ./objs/
SRC_DIR = ./srcs/

# ------------------------------------------------------------------------------

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

INC_DIRS = includes \

INC = $(addprefix -I, $(INC_DIRS))

SRC = philo_one.c \
	  tools.c \
	  print.c \
	  time_tools.c \
	  actions.c \
	  simulation.c \
	  handle_args.c

# ------------------------------------------------------------------------------

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re

# ------------------------------------------------------------------------------

all : $(NAME)

bonus : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@ 

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p objs
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean :
	@echo $(MAGENTA) "Cleaning objs..." $(RESET)
	@rm -rf $(OBJ_DIR)
	@echo $(MAGENTA) "...done" $(RESET)

fclean : clean
	@echo $(MAGENTA) "Total cleaning..." $(RESET)
	@rm -f $(NAME)
	@echo $(MAGENTA) "...done" $(RESET)

re : fclean all
