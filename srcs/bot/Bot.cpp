#include "Bot.hpp"

Bot::Bot() {}
Bot::Bot(const Bot& other) {(void) other;}
Bot& Bot::operator=(const Bot& other) {(void) other; return *this;}
Bot::~Bot() {}

void Bot::checkBotMention(Client* client, Channel* channel, const std::string& message) const
{
    (void) client;
    std::cout << "check bot ping: " << message.find("@BOT") << std::endl;
    if (message.find("@BOT") == 1)
    {
        std::cout << "Bot got pingged!"<<std::endl;
        std::vector<std::string> args = splitToVector(message);
        args.erase(args.begin());

        if (args[0].compare("ping") == 0)
        {
            for (std::size_t index = 0; index < channel->getClients().size(); index++)
            {
                Client* target = channel->getClients()[index];
                target->setSendBuffer(":bot PRIVMSG " + channel->getName() + " PONG!\r\n");
                sendBuffer(*target);
            }
        }
    }
}