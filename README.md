# FT_IRC

Source to help: https://beej.us/guide/bgnet/pdf/bgnet_a4_c_1.pdf
                https://datatracker.ietf.org/doc/html/rfc2812
                https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9

Client: id, username, nickname, addresse, id channel actuel
  -> Client(...), ~Client(), join(int channelId), leave(int channelId),
  string receiveMessage(binaire) -> si binaire
  string receiveMessage(string, int channelId)
  string receivePrivateMessage(string, int userId, int senderId)

Channel: id, Client[] clients, Client[] operators, ChannelSettings settings

ChannelSettings: topic, mode(bool invite_only, ...) + getter / setter mode

Bot: id, name, parseCommand()

sendMessage(int senderId, int channelId, string message), sendPrivateMessage(int senderId, int userId, string msg)

Server:
  Client[], Channel[], port, pass


IRSSI: ---> available on the school computer

    First open IRSSI typing irssi on the bash
    Connect with /connect <ip> <port> <password>
    Then you should start all commands with a / followed by one of the command above.
    You can type /help to see all irssi commands

netcat:

    Type nc <ip> <port> on the bash
    First you have to enter the server password PASS <password>
    Then your nickname NICK <nickname>
    Finally your username, hostname, server name and real name USER <username> <hostname> <server name> <real name>
    If one of those steps went wrong, you have to restart the connexion process.
    Otherwise well played you are connected to the server!
    To use commands now, you have to follow the syntax above.
