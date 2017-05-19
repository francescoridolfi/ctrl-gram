import PluginManager

bot=PluginManager.Bot()

def function(conn):
    data="Ciao!"
    conn.send(data.encode())
    data=conn.recv(1024).decode()
    conn.close()
    return data

bot.setConn("127.0.0.1",8888,"Bot-Voicegram-Test")
print(bot.newConn(function))
