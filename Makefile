# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 14:06:55 by nsamoilo          #+#    #+#              #
#    Updated: 2022/01/06 14:07:42 by nsamoilo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FUNCTIONS = start solve tetro parse_valid_input end input_checks
FILES = $(patsubst %, %.c, $(FUNCTIONS))
OBJECTS = $(patsubst %, %.o, $(FUNCTIONS))

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c $(FILES)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test:
	@for function in $(FUNCTIONS) ; do \
		./eval_tests/tests.sh $$function ; \
	done
