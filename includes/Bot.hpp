#ifndef BOT_HPP
# define BOT_HPP

#include "ft_irc.hpp"

class Bot
{
    public:
        Bot();
        Bot(const Bot& other);
        Bot& operator=(const Bot& other);
        ~Bot();

        void checkBotMention(Client* client, Channel* channel, const std::string& message) const;

};

#endif