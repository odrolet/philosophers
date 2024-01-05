# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oldrolet <oldrolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 15:34:52 by oldrolet          #+#    #+#              #
#    Updated: 2024/01/05 16:01:43 by oldrolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAG = -Wall -Werror -Wextra -O3 #-fsanitize=thread
RM  = rm -fr
SRCS  = src/main.c src/ft_parsing.c src/init.c src/utils.c src/simulation.c src/supervisor.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAG) -o $@

%.o : %.c
	$(CC) $(CFLAG) -o $@ -c $^

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

run: 
	./philo 100 800 200 200