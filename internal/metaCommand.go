package internal

import (
	"fmt"
	"os"
)

type MetaCommandResult int

const (
	META_COMMAND_SUCCESS MetaCommandResult = iota
	META_COMMAND_UNRECOGNIZED_COMMAND
)

func DoMetaCommand(input string) MetaCommandResult {
	if input == ".exit" {
		fmt.Println("Exiting...")
		os.Exit(0)
	}

	return META_COMMAND_UNRECOGNIZED_COMMAND
}
