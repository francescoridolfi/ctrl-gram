package main

import "net"
import "fmt"
import "bufio"
import "os"

func main() {
  IfConfig()
  readerClient := bufio.NewReader(os.Stdin)
  fmt.Print("Connect to : ")
  client, _ := readerClient.ReadString('\n')
  conn, _ := net.Dial("tcp", "127.0.0.1:8081")
  SendIdentity(conn)
  fmt.Fprintf(conn, client+"\n")
  for {
		// read in input from stdin
		reader := bufio.NewReader(os.Stdin)
		fmt.Print("Text to send: ")
		text, _ := reader.ReadString('\n')
    // send to socket
		fmt.Fprintf(conn, text+"\n")
		// listen for reply
		message, _ := bufio.NewReader(conn).ReadString('\n')
		fmt.Print("Message from server: " + message)
	}
}
