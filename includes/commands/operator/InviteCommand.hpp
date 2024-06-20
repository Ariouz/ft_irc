#ifndef INVITE_COMMAND_HPP
# define INVITE_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class InviteCommand : public Command
{
    public:
        InviteCommand(const std::string& name);
        ~InviteCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server);
};

#endif