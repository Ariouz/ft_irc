NAME = ircserv
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98 
INCLUDES = -I./includes

SRCS =	srcs/main.cpp\
		srcs/classes/Client.cpp\
		srcs/classes/Server.cpp\
		srcs/classes/Channel.cpp\
		srcs/classes/Message.cpp\
		srcs/comands/cap.cpp\
		srcs/comands/nick.cpp\
		srcs/comands/pass.cpp\
		srcs/comands/user.cpp\
		srcs/comands/ping.cpp\
		srcs/comands/pong.cpp\
		srcs/comands/join.cpp\
		srcs/comands/invite.cpp\
		srcs/comands/kick.cpp\
		srcs/comands/part.cpp\
		srcs/comands/privmsg.cpp\
		srcs/comands/quit.cpp\
		srcs/comands/topic.cpp\
		srcs/utils/ft_stoi.cpp\
		srcs/utils/ft_split.cpp\
		srcs/utils/send_buffer.cpp\
		srcs/utils/VectorToString.cpp

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