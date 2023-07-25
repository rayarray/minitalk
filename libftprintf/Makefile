# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 11:52:06 by rleskine          #+#    #+#              #
#    Updated: 2023/02/26 14:19:20 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
HDR		=	../libft
LIB		=	libft
CFLAGS	=	-Wall -Wextra -Werror 
# -fsanitize=address

SRC =	ft_printf.c ft_printf_utils1.c ft_printf_utils2.c ft_printf_utils3.c ft_printf_utils4.c ft_printf_convert1.c
OBJ =	$(SRC:.c=.o)
CC =	cc

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^ 
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HDR) -c $< -o $@

$(LIB):
	$(MAKE) -C ../$(LIB)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.SILENT:
