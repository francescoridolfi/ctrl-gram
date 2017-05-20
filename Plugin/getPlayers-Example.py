#import the framework
import PluginManager

#define the root
server=PluginManager.Voicegram()

#set connection to server(ip,port) the 8887 port is the PluginPort of VoiceGram
server.setServer("127.0.0.1",8887)

#get players in the server 
players=server.getPlayers()

#print the result
print(players)

