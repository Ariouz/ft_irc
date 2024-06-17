#ifndef PASS_COMMAND_HPP
# define PASS_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class PassCommand : public Command
{
    public:
        PassCommand(const std::string& name);
        ~PassCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* sender, Server& server);
};

#endif