#ifndef KICK_COMMAND_HPP
# define KICK_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class KickCommand : public Command
{
    public:
        KickCommand(const std::string& name);
        ~KickCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server);
};

#endif