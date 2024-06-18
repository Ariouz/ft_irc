#ifndef PONG_COMMAND_HPP
# define PONG_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class PongCommand : public Command
{
    public:
        PongCommand(const std::string& name);
        ~PongCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* sender, Server& server);
};

#endif