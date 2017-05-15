#!/usr/lib/python
#Require python3.x
#VOICEGRAM PluginManager.py v1.0 BETA
#DEVELOPED BY ridolfino AND SourceCode2

import socket

class Voicegram():
  result=""
  HOST=""
  PORT=5000
  def conn(self,cmd):
    HOST = self.HOST
    PORT = self.PORT

    conn = socket.socket()
    conn.connect((HOST,PORT))

    while self.send==False:
      if(cmd=="getPlayers"):
        data="getPlayers"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        self.result=data
        conn.close()
        return data
      if(cmd=="connect"):
        data="getPlayers"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        conn.close()
        self.result=data
        return data
      if(cmd=="join"):
        data="join"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        self.result = data
        conn.close()
        return data
      if(cmd=="msg"):
        data="msg"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        self.result = data
        conn.close()
        return data
    conn.close()
  def getPlayers(self):
      return self.conn("getPlayers")
  def connect(self):
      return self.conn("connect")
  def getEvent(self,e):
    if(e=="onJoin"):
        return self.conn("join")
    if(e=="onMsg"):
        return self.conn("msg")
  def setServer(self,ip,port):
    self.HOST=ip
    self.PORT=port
