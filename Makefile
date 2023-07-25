# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/03/15 16:51:24 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	client server
LIBS		=	./libft/libft.a ./libftprintf/libftprintf.a
LIBDIR		=	$(basename $(notdir $(LIBS)))
INCLUDE		=	$(addprefix -I, $(LIBDIR)) $(addprefix -L, $(LIBDIR))
LIBFLAGS	=	-lft -lftprintf
CFLAGS		=	-Wall -Wextra -Werror 
# -fsanitize=address

CC =	cc

all: $(LIBS) $(NAME)

$(NAME): %: ./basic/%.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFLAGS) -o $@ $<

$(LIBS): %:
	$(MAKE) -C $(basename $(notdir $@))

bonus: $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFLAGS) -o client ./bonus/client.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFLAGS) -o server ./bonus/server.c

clean:
	$(foreach lib, $(LIBDIR), $(MAKE) -C $(lib) clean;)

fclean: clean
	$(foreach lib, $(LIBDIR), $(MAKE) -C $(lib) fclean;)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: bonus