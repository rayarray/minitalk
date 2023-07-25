# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 11:52:06 by rleskine          #+#    #+#              #
#    Updated: 2023/03/14 18:24:31 by rleskine         ###   ########.fr        #
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

$(NAME): %: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFLAGS) -o $@ $<

$(LIBS): %:
	$(MAKE) -C $(basename $(notdir $@))

#$(LIBS):
#	$(MAKE) -C $(LIBS)

clean:
	$(foreach lib, $(LIBDIR), $(MAKE) -C $(lib) clean;)

fclean: clean
	$(foreach lib, $(LIBDIR), $(MAKE) -C $(lib) fclean;)
	/bin/rm -f $(NAME)

re: fclean all
