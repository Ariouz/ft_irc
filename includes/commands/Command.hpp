#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "ft_irc.hpp"

class Command
{
    public:
        Command();
        virtual ~Command();
    
        virtual void        execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server) = 0;

        const std::string&  getName(void) const;

    protected:
        std::string _name;

};

# endif