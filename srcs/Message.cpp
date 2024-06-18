# include "Message.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "ChannelSettings.hpp"

std::string& Message::RPL_WELCOME( Client& client) 
{
    static std::string res;
    res = "001 " + client.getUsername() + " :Welcome to the ft_irc Network, " + client.getNickname() + "\r\n";
    return res;
}

std::string& Message::ERR_SASLFAIL(const std::string& username) 
{
    static std::string res;
    res = "904 " + username + " :SASL authentication failed\r\n";
    return res;
}

std::string& Message::ERR_NOPRIVS(const std::string& username, const std::string& privilege) 
{
    static std::string res;
    res = "723 "  + username + " " + privilege + " :Insufficient oper privileges.\r\n";
    return res;
}

std::string& Message::ERR_UMODEUNKNOWNFLAG(const std::string& username) 
{
    static std::string res;
    res = "501 "  + username + " :Unknown MODE flag\r\n";
    return res;
}

std::string& Message::ERR_NEEDMOREPARAMS(const std::string& username, const std::string& cmd) 
{
    static std::string res;
    res = "461 " + username + " "+cmd+" :Not enough parameters\r\n";
    return res;
}

std::string& Message::ERR_NOSUCHCHANNEL(const std::string& username, const std::string& channel)
{
    static std::string res;
    res = "403 " + username + " " + channel + " :No such channel\r\n";
    return res;
}

std::string& Message::ERR_INVITEONLYCHAN(const std::string& username, const std::string& channel)
{
    static std::string res;
    res = "473 " + username + " " + channel + " :Cannot join channel (+i)\r\n";
    return res;
}

std::string& Message::ERR_BADCHANNELKEY(const std::string& username, const std::string& channel)
{
    static std::string res;
    res = "475 "+username+ " " + channel + " :Cannot join channel (+k)\r\n";
    return res;
}

std::string& Message::RPL_TOPIC(const std::string& username, const std::string& channel, const std::string& topic)
{
    static std::string res;
    res = "332 "+username+ " " + channel + " :" + topic + "\r\n";
    return res;
}

std::string& Message::RPL_NAMREPLY(Client& client, const Channel& channel)
{
    (void) channel;
    (void) client;
    static std::string res;
    std::string prefix = "";
    //std::cout << "fd: " << client.getFd() << " \n";
    //std::string prefix = channel.isOperator(client.getFd()) ? "@" : "";
    //std::cout << client.getUsername() << std::endl;
    /*std::cout << channel.getName() + " \n";
    std::cout << prefix + " \n";
    std::cout << "nickane:" + client.getNickname() + " \n";*/
    res = "353 TEST = test :test\r\n";//"353 " + client.getUsername() + " = " + channel.getName() + " :" + prefix + client.getNickname() + "\r\n";
    return res;
}

std::string& Message::RPL_ENDOFNAMES(Client& client, const Channel& channel)
{
    static std::string res;
    res = "366 "+client.getUsername()+ " " + channel.getName() + " :End of /NAMES list\r\n";
    return res;
}

std::string& Message::ERR_ALREADYREGISTERED(const std::string& username)
{
    static std::string res;
    res = "462 "  + username + " :You may not reregister\r\n";
    return res;
}

std::string& Message::ERR_NONICKNAMEGIVEN(const std::string& username)
{
    static std::string  res;
    res = "431 " + username + " :No nickname given\r\n";
    return (res);
}

std::string& Message::ERR_ERRONEUSNICKNAME(const std::string& username, const std::string& argv)
{
    static std::string res;
    res = "432 " + username + argv + " :Erroneus nickname/r/n";
    return res;
}

std::string& Message::ERR_NICKNAMEINUSE(const std::string& username, const std::string& argv)
{
    static std::string res;
    res = "433 " + username + argv + " :Nickname is already in use\r\n";
    return (res);
}

std::string& Message::ERR_NOTEXTTOSEND(const std::string& username)
{
    static std::string res;
    res = "412 " + username + " :No text to send\r\n";
    return (res);
}