package db

import (
	"fmt"
	"os"
)

type MetaCommandResult int

const (
	MetaCommandSuccess MetaCommandResult = iota
	MetaCommandUnrecognizedCommand
)

func DoMetaCommand(input string) MetaCommandResult {
	if input == ".exit" {
		fmt.Println("Exiting...")
		os.Exit(0)
	}

	return MetaCommandUnrecognizedCommand
}

func ParseMetaCommand(command string) bool {
	if command[0] == '.' {
		switch DoMetaCommand(command) {
		case MetaCommandSuccess:
			return true
		case MetaCommandUnrecognizedCommand:
			fmt.Printf("Unrecognized command: %s\n", command)
			return true
		}
	}
	return false
}
