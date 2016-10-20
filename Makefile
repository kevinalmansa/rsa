##
## Makefile for RSA in /home/ksa28/Kent/RSA
## 
## Made by Kevin Almansa
## Login   <ksa28>
## 
## Started on  Mon Jan 18 18:52:45 2016 Kevin Almansa
## Last update Mon Jan 18 22:15:45 2016 Kevin Almansa
##

RM		= rm -f
CC		= gcc

NAME		= rsa
NAME_TESTS	= rsa_tests

CFLAGS		= -Iinclude/ -W -Wall -Wextra -march=native -ggdb3
LDFLAGS		= -lm

SRCS_TEST	= src/modulars.c			\
		  src/primes.c				\
		  src/rsa.c				\
		  src/tests_main.c
OBJS_TEST	= $(SRCS_TEST:.c=.o)

SRCS		= src/modulars.c			\
		  src/primes.c				\
		  src/rsa.c				\
		  src/main.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

tests: $(OBJS_TEST)
	$(CC) -o $(NAME_TESTS) $(OBJS_TEST) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(OBJS_TEST)

fclean: clean
	$(RM) $(NAME) $(NAME_TESTS)

re: fclean all

re-tests: fclean tests
