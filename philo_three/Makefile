# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/03 12:23:24 by darbib            #+#    #+#              #
#    Updated: 2021/03/25 12:02:00 by darbib           ###   ########.fr        #
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
CHECK =		'\xE2\x9C\x94'

NAME = philo_three
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

HEADERS = philo_three.h

SRC = philo_three.c \
	  tools.c \
	  print.c \
	  time_tools.c \
	  actions.c \
	  simulation.c \
	  destroy.c \
	  handle_args.c

# ------------------------------------------------------------------------------

vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIRS)

.PHONY: all clean fclean re

# ------------------------------------------------------------------------------

all : $(NAME)

bonus : $(NAME)

$(NAME): $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@ 
	@echo $(GREEN) $@ "is builded !" $(CHECK) $(RESET) 

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p objs
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@
	@echo $(BLUE) "compiling" $< $(RESET)

clean :
	@echo $(MAGENTA) "Cleaning objs..." $(RESET)
	@rm -rf $(OBJ_DIR)
	@echo $(MAGENTA) "...done" $(RESET)

fclean : clean
	@echo $(MAGENTA) "Total cleaning..." $(RESET)
	@rm -f $(NAME)
	@echo $(MAGENTA) "...done" $(RESET)

re : fclean all
