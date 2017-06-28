package control
import (
  "os"
  "fmt"
  "bufio"
  "io/ioutil"
)
func CreateConfig() {
  inputReader := bufio.NewReader(os.Stdin)
  fmt.Println("Inserisci il tuo codename: ")
  input,_ := inputReader.ReadString('\n')
  ioutil.WriteFile("/etc/ctrl-gram.conf", contents, 0x644);
}
/*==Controllare se esiste la config==*/
func IfConfig()  {
    path := "/etc/ctrl-gram.conf"
    _, err := os.Stat(path);
    if (os.IsNotExist(err)) {
      fmt.Printf("\033[1;31m[ERROR]\tIl file di configurazione non esiste")
      CreateConfg()
    }
}
