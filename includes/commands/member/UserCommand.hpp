#ifndef USER_COMMAND_HPP
# define USER_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class UserCommand : public Command
{
    public:
        UserCommand(const std::string& name);
        ~UserCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* sender, Server& server);
};

#endif