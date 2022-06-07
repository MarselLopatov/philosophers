NAME = philo

HEADER = philo.h

SRCS =	init.c \
		philo.c \
		valid.c \
		philo_work.c \
		philo_start.c \
		utils.c \

OBJ = $(patsubst %.c, %.o, $(SRCS))

CC = gcc
FLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -I $(HEADER) -o $@

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus