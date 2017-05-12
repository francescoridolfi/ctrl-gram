#!/usr/lib/python
#Require python3.x
#VOICEGRAM PluginManager.py v1.0 BETA
#DEVELOPED BY ridolfino AND SourceCode2

import socket

class Voicegaming():
  players=""
  def conn(self,cmd):
    HOST = ""
    PORT = 5000
    conn = socket.socket()
    conn.connect((HOST,PORT))
    if(cmd=="getPlayers"):
      conn.send("getPlayers")
      data=conn.recv(1024).decode()
      players=data
      conn.close()
      return getPlayers()
  def getPlayers(self):
    conn("getPlayers")
    return players
    
    

