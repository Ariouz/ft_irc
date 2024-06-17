#ifndef COMMAND_MANAGER_HPP
# define COMMAND_MANAGER_HPP

# include "ft_irc.hpp"
# include "Command.hpp"

class CommandManager
{

    public:
        CommandManager();
        ~CommandManager();

        void        registerAll(void);
        void        registerCommand(Command* command);
        void        execute(const std::string& req, Client* client, Channel* channel, Server& server);

        Command*    getCommand(const std::string& name);
        bool        isCommand(const std::string& req);

    private:
        std::vector<Command*> _commands; 

};

#endif
