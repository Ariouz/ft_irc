#ifndef PART_COMMAND_HPP
# define PART_COMMAND_HPP

# include "commands/Command.hpp"
# include "ft_irc.hpp"

class PartCommand : public Command
{
    public:
        PartCommand(const std::string& name);
        ~PartCommand();

        virtual void execute(const std::vector<std::string> args, Channel* channel, Client* sender, Server& server);
};

#endif