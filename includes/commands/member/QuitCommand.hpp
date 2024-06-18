#ifndef QUIT_COMMAND_HPP
# define QUIT_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class QuitCommand : public Command
{
    public:
        QuitCommand(const std::string& name);
        ~QuitCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server);
};

#endif