#import the framework
import PluginManager

#define the root
server=PluginManager.Voicegram()

#for open a request
server.getPlayers()

#for split the players in array
players=server.getPlayers()
z=players.split("///")

#print the result
print(z)
