package main
import (
  "fmt"
  /*"io/ioutil"*/
  "os"
  "bufio"
  "net"
)
func SendIdentity(conn net.Conn)  {
  /*zita, err := ioutil.ReadFile("/etc/ctrl-gram.conf")
  if (err != nil) {
    IfConfig()
  }
  identity := string(zita)*/
  readerClient := bufio.NewReader(os.Stdin)
  fmt.Print("Codename : ")
  identity, _ := readerClient.ReadString('\n')
  fmt.Fprintf(conn, identity + "\n")
}
