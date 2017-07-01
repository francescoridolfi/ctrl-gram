package main
import (
  "os"
  "fmt"
  "bufio"
  "io/ioutil"
)

/*== Creare /etc/ctrl-gram.conf ==*/
func CreateConfig() {
  uid := os.Getuid()
  if (uid != 0) {
    fmt.Println("\033[1;31m[ERROR]\tPer creare la config devi avviare ctrl-tab usando su/sudo\033[0;0m");
    os.Exit(1)
  }
  inputReader := bufio.NewReader(os.Stdin)
  fmt.Printf("\033[1;36mInserisci il tuo codename: \033[0;0m")
  input,_ := inputReader.ReadString('\n')
  ioutil.WriteFile("/etc/ctrl-gram.conf", []byte(input), 0x644);
}

/*==Controllare se esiste la config==*/
func IfConfig() {
    path := "/etc/ctrl-gram.conf"
    _, err := os.Stat(path);
    if (os.IsNotExist(err)) {
      fmt.Println("\033[1;31m[ERROR]\tIl file di configurazione non esiste\033[0;0m")
      CreateConfig()
    }
}
