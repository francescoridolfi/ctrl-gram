package main

import(
	"net"
	"fmt"
	"bufio"
	//"strings"
)
func listen(conn net.Conn, my_channel chan string, to_talk_channel chan string)  {
	for {
		select {
		case my_message := <- my_channel:
			conn.Write([]byte(my_message+"\n"))
		}
	}
}
func handler(conn net.Conn, my_channel chan string, to_talk_channel chan string)  {
	fmt.Println("Started func Handler")
	go listen(conn, my_channel, to_talk_channel)
	for {
		message, _ := bufio.NewReader(conn).ReadString('\n')
    if message == "" {
			return
		}
		to_talk_channel <- message
		fmt.Print("Message Received: ", string(message))
		//newmessage := strings.ToUpper(message)
		//conn.Write([]byte(newmessage + "\n"))
	}
}

func preHandler(clients map[string]chan string, IsClients map[string]bool, conn net.Conn)  {
  fmt.Println("Func preHandler")
	identity, _ := bufio.NewReader(conn).ReadString('\n')
	to_talk, _ := bufio.NewReader(conn).ReadString('\n')
	fmt.Println("OK1")
	clients[identity] = make(chan string)
	fmt.Println("OK2")
	IsClients[identity] = true
	fmt.Println("Waiting")
	for (IsClients[to_talk] == false){}
	fmt.Println("Starting func handler")
	go handler(conn, clients[identity], clients[to_talk])
  fmt.Println("Exit func preHandler")
	return
}

func main() {
  /*== Declare ==*/
	var clients map[string]chan string
	clients = make(map[string]chan string)
	var IsClients map[string]bool
	IsClients = make(map[string]bool)
	IfConfig()
	fmt.Println("Launching server...")
	ln, _ := net.Listen("tcp", ":8081")

  for {
	conn, _ := ln.Accept()
  go preHandler(clients, IsClients, conn)
  }
}
