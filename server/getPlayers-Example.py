#import the framework
import PluginManager

#set server access point
server.setServer("127.0.0.1",5000)

#define the root
server=PluginManager.Voicegram()

#for open a request
server.connect()

#for split the players in array
players=server.getPlayers()
z=players.split("///")

#print the result
print(z)
