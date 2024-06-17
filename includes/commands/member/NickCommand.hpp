#ifndef NICK_COMMAND_HPP
# define NICK_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class NickCommand : public Command
{
    public:
        NickCommand(const std::string& name);
        ~NickCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server);
};

#endif