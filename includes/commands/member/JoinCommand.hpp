#ifndef JOIN_COMMAND_HPP
# define JOIN_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class JoinCommand : public Command
{
    public:
        JoinCommand(const std::string& name);
        ~JoinCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server);
};

#endif