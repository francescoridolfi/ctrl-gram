package main
import (
	"fmt"
)
func prova(clients map[string]chan string) {
	for {
	if(clients["prova"]=="0xc420016120"){}
	}
	fmt.Println("Urrra")
}
func main() {
	var clients map[string]chan string
	clients = make(map[string]chan string)
	fmt.Println(clients["prova"])
	//go prova(clients)
	clients["prova"] = make(chan string)
	fmt.Println("Dopo ", clients["prova"])
	for{}
}
