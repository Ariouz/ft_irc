#ifndef MODE_COMMAND_HPP
# define MODE_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class ModeCommand : public Command
{
    public:
        ModeCommand(const std::string& name);
        ~ModeCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server);
};

#endif