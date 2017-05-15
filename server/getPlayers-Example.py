#import the framework
import PluginManager

#define the root
server=PluginManager.Voicegram()

#set server access point
server.setServer("127.0.0.1",8888)

#get players in the server 
players=server.getPlayers()

#print the result
print(players)

