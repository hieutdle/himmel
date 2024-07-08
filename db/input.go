package db

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func PrintPrompt() {
	fmt.Print("db > ")
}

func ReadInput() string {
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	return strings.TrimSpace(input)
}
