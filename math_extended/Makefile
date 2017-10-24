# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/10 20:24:37 by ykolomie          #+#    #+#              #
#    Updated: 2017/09/30 14:47:32 by ykolomie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmathx.a
SRC_FILES = vector2_part1.c \
            vector2_part2.c \
            vector3_part1.c \
            vector3_part2.c \
            hvector.c       \
            matrix2.c       \
            matrix3.c       \
            matrix4_part1.c \
            matrix4_part2.c \
			complex_number_part1.c \
			complex_number_part2.c 

OBJDIR = ./obj/

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRCDIR), $(SRC_FILES))

OBJ = $(addprefix $(OBJDIR), $(OBJ_FILES))

CC = clang

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		   ar rcs $(NAME) $(OBJ)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ): |$(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJDIR)

re: clean all
