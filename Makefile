NAME = ircserv
CC = c++
CFLAGS = -g -Wall -Wextra -std=c++98 #-Werror 
INCLUDES = -I./includes

SRCS =	srcs/main.cpp\
		srcs/Client.cpp\
		srcs/Server.cpp\

OBJS = $(SRCS:.cpp=.o)

.cpp.o: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re