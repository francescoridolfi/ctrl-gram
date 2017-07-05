#!/usr/lib/python2

import socket

class Plugin():
    host = "127.0.0.1"
    port = 8887


    def conn(self):
        conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        conn.connect((self.host, self.port))
        return(conn)

    def execute(self, conn, msg):
        conn.send(msg.encode())
        data=conn.recv(4096)
        return(data.decode())

    def getOnline(self, conn):
        msg="getOnline"
        conn.send(msg.encode())
        data=conn.recv(4096)
        return(data.decode())

    
    def getPlayerInfo(self, conn, user="", uuid="", ip="", mac=""):
        msg=""
        if user != "":
            msg="infoPlayerUSER "+user
        if uuid != "":
            msg="infoPlayerUUID "+uuid
        if ip != "":
            msg="infoPlayerIP "+ip
        if mac != "":
            msg="infoPlayerMAC "+mac
        if(msg!=""):
            conn.send(msg.encode())
            data=conn.recv(4096)
            return(data.decode())
        
        
        

    def setConn(self, host, port):
        self.host=host
        self.port=port



class Bot():

    host = "127.0.0.1"
    port = 8888

    def conn(self):
        print(self.host)
        print(self.port)
        conn="connected"
        return conn

    def setConn(self, host, port):
        self.host=host
        self.port=port
