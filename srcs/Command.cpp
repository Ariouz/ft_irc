#include "Command.hpp"

Command::Command(const std::string name, const std::vector<std::string> args, Channel& channel, Client& sender) : 
    _name(name), _args(args), _channel(channel), _sender(sender) {}

Command::~Command() {}