# include "Message.hpp"
# include "Client.hpp"

std::string& Message::RPL_WELCOME(const Client& client) 
{
    static std::string res = "001 " + client.getUsername() +  " :Welcome to the ft_irc Network, " + client.getNickname() + "\r\n";
    return res;
}

std::string& Message::ERR_SASLFAIL(const std::string& username) 
{
    static std::string res = "904 " + username + " :SASL authentication failed\r\n";
    return res;
}

std::string& Message::ERR_NOPRIVS(const std::string& username, const std::string& privilege) 
{
    static std::string res = "723 "  + username + " " + privilege + " :Insufficient oper privileges.\r\n";
    return res;
}

std::string& Message::ERR_UMODEUNKNOWNFLAG(const std::string& username) 
{
    static std::string res = "501 "  + username + " :Unknown MODE flag\r\n";
    return res;
}
