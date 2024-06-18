#include "commands/Command.hpp"

Command::Command() {}

Command::~Command() {}

const std::string& Command::getName(void) const
{
    return this->_name;
}