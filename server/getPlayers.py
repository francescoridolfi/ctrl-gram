#import the framwork
import PluginManager

#define the root
server=PluginManager.Voicegam()

#for open a request
server.getPlayers()

#for split the players string in array
players=server.getPlayers()
z=players.split("///")

#print the result
print(z)
