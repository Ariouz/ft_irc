#ifndef PING_COMMAND_HPP
# define PING_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class PingCommand : public Command
{
    public:
        PingCommand(const std::string& name);
        ~PingCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* sender, Server& server);
};

#endif