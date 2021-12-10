# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/07 22:34:10 by rmatsuka          #+#    #+#              #
#    Updated: 2021/07/23 16:52:40 by rmatsuka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
SRCS	=	main.c \
			ph_init.c \
			ph_utils1.c \
			ph_utils2.c \
			ph_actions.c \
			ph_routines.c \

OBJS	=	$(SRCS:.c=.o)
RM		=	rm -f
CC		= 	gcc -pthread
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME) ## Compile

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean: ## Delete *.o file
	$(RM) $(OBJS)

fclean: clean ## Delete *.o file and philo
	$(RM) $(NAME)

re: fclean all ## Recompile

.PHONY: all clean fclean re help sani

sani: CFLAGS += -fsanitize=thread ## Add sanitizer and recompile
sani: re

test1: all ## ./philo 1 100 100 100
	./philo 1 100 100 100

test2: all ## ./philo 2 410 200 200
	./philo	2 410 200 200

test3: all ## ./philo 5 800 200 200
	./philo	5 800 200 200

test4: all ## ./philo 2 410 200 200 3
	./philo	2 410 200 200 3

.PHONY: test1 test2 test3 test4

help:
	@grep -E '^[a-zA-Z1-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
