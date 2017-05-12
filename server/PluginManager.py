#!/usr/lib/python
#Require python3.x
#VOICEGRAM PluginManager.py v1.0 BETA
#DEVELOPED BY ridolfino AND SourceCode2

import socket

class Voicegram():
  players=""
  send=False
  def conn(self,cmd):
    HOST = "127.0.0.1"
    PORT = 5000

    conn = socket.socket()
    conn.connect((HOST,PORT))

    while self.send==False:
      if(cmd=="getPlayers"):
        data="getPlayers"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        self.players=data
        conn.close()
        self.send=True
        return self.getPlayers()
      if(cmd=="connect"):
        data="connect"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        conn.close()
        self.send=True
        return self.connect()
    conn.close()
  def getPlayers(self):
    if(self.send==False):
      self.conn("getPlayers")
    else:
      self.send=True
      return self.players
  def connect(self):
    if(self.send==False):
      return self.conn("connect")
    else:
      self.send=False
      return "Connect!"
