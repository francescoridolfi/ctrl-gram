import PluginManager

server=PluginManager.Plugin()

server.setConn("127.0.0.1",5000)

myConn = server.conn()


"""
Execute method:

result=server.execute(myConn, "getOnline")

print(result)
"""

"""
getOnline method:

result=server.getOnline(myConn)

print(result)
"""
