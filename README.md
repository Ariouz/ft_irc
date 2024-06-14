# FT_IRC

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
