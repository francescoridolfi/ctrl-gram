package main

<<<<<<< HEAD
import(
	"net"
	"fmt"
	"bufio"
	"strings"
)
func handler(conn net.Conn)  {
=======
import "net"
import "fmt"
import "bufio"
import "strings" // only needed below for sample processing

func main() {

	fmt.Println("Launching server...")

	// listen on all interfaces
	ln, _ := net.Listen("tcp", ":8081")

	// accept connection on port
	conn, _ := ln.Accept()

	// run loop forever (or until ctrl-c)
>>>>>>> 519a5b9045dd529e2e33187468bd3f012e6f85c7
	for {
		// will listen for message to process ending in newline (\n)
		message, _ := bufio.NewReader(conn).ReadString('\n')
		// output message received
		fmt.Print("Message Received: ", string(message))
		// sample process for string received
		newmessage := strings.ToUpper(message)
		// send new string back to client
		conn.Write([]byte(newmessage + "\n"))
	}
}
func main() {

	fmt.Println("Launching server...")

	// listen on all interfaces
	ln, _ := net.Listen("tcp", ":8081")

	// accept connection on port
  for {
	conn, _ := ln.Accept()
	go handler(conn)
  }
}
