#!/usr/lib/python
#Require python3.x
#VOICEGRAM PluginManager.py v1.0 BETA
#DEVELOPED BY ridolfino AND SourceCode2

import socket

class Voicegram():
  result=None
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
        self.result=data
        conn.close()
        self.send=True
        return self.getPlayers()
      if(cmd=="connect"):
        data="getPlayers"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        conn.close()
        self.send=True
        self.result=data
        return self.connect()
      if(cmd=="join"):
        data="join"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        self.result = data
        conn.close()
        self.send=True
        return self.getEvent("onJoin")
      if(cmd=="msg"):
        data="msg"
        conn.send(data.encode())
        data=conn.recv(1024).decode()
        self.result = data
        conn.close()
        self.send=True
        return self.getEvent("onMsg")
    conn.close()
  def getPlayers(self):
    if(self.send==False):
      self.conn("getPlayers")
    else:
      self.send=True
      res=self.result
      self.result=None
      return res
  def connect(self):
    if(self.send==False):
      return self.conn("connect")
    else:
      res=self.result
      self.result=None
      return res
  def getEvent(self,e):
    if(e=="onJoin"):
      if(self.send==False):
        self.conn("join")
      else:
        res=self.result
        self.result=None
        return res
    if(e=="onMsg"):
      if(self.send==False):
        self.conn("msg")
      else:
        res=self.result
        self.result=None
        return res
