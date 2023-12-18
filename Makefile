NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

DIR = srcs
SRCS_RAW = philo.c execute.c
SRCS = $(addprefix $(DIR)/,$(SRCS_RAW)) \

OBJS = $(SRCS:c=o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(DEBUG) -o $(NAME)
clean:
	rm $(OBJS) $(OBJB) -f
fclean: clean 
	rm $(NAME) -f
re: fclean all

%.o: %.c def.h
	$(CC) -c $< -o $@ $(DEBUG)$(CFLAGS) $(INCLUDES)

test :
	./philo 5 800 200 200

debug :
	lldb ./philo -o "b main" -o "run 5 800 200 200"

