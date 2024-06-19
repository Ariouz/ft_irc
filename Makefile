NAME = ircserv
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -std=c++98 -g
INCLUDES = -I./includes

SRCS =	$(addprefix srcs/, \
	main.cpp \
	Client.cpp \
	Server.cpp \
	Channel.cpp \
	ChannelSettings.cpp \
	utils.cpp \
	Message.cpp \
) $(addprefix srcs/commands/, \
	Command.cpp \
	CommandManager.cpp \
	other/CapCommand.cpp \
	other/PingCommand.cpp \
	other/PongCommand.cpp \
	member/NickCommand.cpp \
	member/PassCommand.cpp \
	member/UserCommand.cpp \
	member/JoinCommand.cpp \
	member/QuitCommand.cpp \
	member/PrivMsgCommand.cpp \
	member/PartCommand.cpp \
	operator/ModeCommand.cpp \
)

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