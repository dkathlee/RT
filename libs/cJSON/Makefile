# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 10:50:38 by marvin            #+#    #+#              #
#    Updated: 2020/11/22 10:50:38 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libjson.a

FLAGS = -Wall -Wextra -Werror

SRCS = cJSON.c

OUT = cJSON.o

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(SRCS)
	ar rc $(NAME) $(OUT)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OUT)

fclean : clean
	/bin/rm -f $(NAME)

re: fclean all
