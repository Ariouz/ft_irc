# include "commands/CommandManager.hpp"

# include "commands/other/CapCommand.hpp"
# include "commands/other/PingCommand.hpp"
# include "commands/other/PongCommand.hpp"
# include "commands/member/PassCommand.hpp"
# include "commands/member/NickCommand.hpp"
# include "commands/member/UserCommand.hpp"
# include "commands/member/JoinCommand.hpp"
# include "commands/operator/ModeCommand.hpp"

CommandManager::CommandManager() {}
CommandManager::~CommandManager()
{
    for (std::size_t index = 0; index < this->_commands.size(); index++)
    {
        delete this->_commands[index];
    }
    this->_commands.clear();
}

void    CommandManager::registerAll()
{
    this->_commands.push_back(new CapCommand("CAP"));
    this->_commands.push_back(new PassCommand("PASS"));
    this->_commands.push_back(new NickCommand("NICK"));
    this->_commands.push_back(new UserCommand("USER"));
    this->_commands.push_back(new ModeCommand("MODE"));
    this->_commands.push_back(new PingCommand("PING"));
    this->_commands.push_back(new PongCommand("PONG"));
    this->_commands.push_back(new JoinCommand("JOIN"));
}

bool    CommandManager::isCommand(const std::string& req)
{
    if (req.empty() || splitToVector(req)[0].empty())
        return (false);
    std::cout << "Check command for " + req << " -> " << (getCommand(splitToVector(req)[0]) != NULL) << std::endl;
    return getCommand(splitToVector(req)[0]) != NULL;
}

void    CommandManager::registerCommand(Command* command)
{
    if (getCommand(command->getName()) != NULL) return ;
    this->_commands.push_back(command);
}

void CommandManager::execute(const std::string& req, Client* client, Channel* channel, Server& server)
{
    std::vector<std::string>    args = splitToVector(req);
    std::string                 name = args[0];
    args.erase(args.begin());
    Command* command = getCommand(name);
    command->execute(args, channel, client, server);
    args.clear();
}

Command* CommandManager::getCommand(const std::string& name)
{
    for (std::size_t index = 0; index < this->_commands.size(); ++index)
    {
        if (this->_commands[index]->getName().compare(name) == 0)
            return this->_commands[index];
    }
    return NULL;
}