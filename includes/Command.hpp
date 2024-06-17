#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "ft_irc.hpp"

class Command
{
    public:
        Command(const std::string name, const std::vector<std::string> args, Channel& channel, Client& sender);
        virtual ~Command();
    
        virtual void            execute() = 0;

        const std::string               getName(void) const;
        const std::vector<std::string>  getArgs(void) const;
        const Channel&                  getChannel() const;
        const Client&                   getClient() const;

    private:
        std::string                 _name;
        std::vector<std::string>    _args;
        Channel&                    _channel;
        Client&                     _sender;
        
};

# endif