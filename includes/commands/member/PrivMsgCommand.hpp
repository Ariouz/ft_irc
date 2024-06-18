#ifndef PRIV_COMMAND_HPP
# define PRIV_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class PrivMsgCommand : public Command
{
    public:
        PrivMsgCommand(const std::string& name);
        ~PrivMsgCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server);
};

#endif