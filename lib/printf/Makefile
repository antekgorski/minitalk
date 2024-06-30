# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agorski <agorski@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 10:23:20 by agorski           #+#    #+#              #
#    Updated: 2024/04/30 12:31:11 by agorski          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libftprintf.a
LIBFTNAME= libft.a
CC= cc
CFLAGS= -Wall -Wextra -Werror
LIBTFDIR= ./libft

SRC= ft_printf.c print_char.c print_string.c print_hex.c print_number.c \
print_unsigned.c print_pointer.c

OBJ= $(SRC:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): libft $(OBJ)
	ar rcs $(NAME) $(OBJ)

libft:
	@make -C $(LIBTFDIR)
	@cp $(LIBTFDIR)/$(LIBFTNAME) .
	@mv $(LIBFTNAME) $(NAME)

clean:
	rm -f *.o

cleanlibft:
	@make clean -C $(LIBTFDIR)

fclean: clean
	rm -f $(NAME)

fcleanlibft:
	@make fclean -C $(LIBTFDIR)

allclean: clean cleanlibft

allfclean: fclean fcleanlibft
	rm a.out

re: fclean fcleanlibft all

testl:
	nm libftprintf.a

test:
	cc ft_printf.c -L. -lftprintf

.PHONY: all libft clean cleanlibft fclean fcleanlibft allclean allfclean re test testl