#ifndef CAP_COMMAND_HPP
# define CAP_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class CapCommand : public Command
{
    public:
        CapCommand(const std::string& name);
        ~CapCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* sender, Server& server);
};

#endif