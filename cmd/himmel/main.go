package main

import (
	"fmt"

	"github.com/hieutdle/himmel/internal"
)

func main() {
	for {
		internal.PrintPrompt()
		input := internal.ReadInput()

		if len(input) > 0 && input[0] == '.' {
			switch internal.DoMetaCommand(input) {
			case internal.META_COMMAND_SUCCESS:
				continue
			case internal.META_COMMAND_UNRECOGNIZED_COMMAND:
				fmt.Printf("Unrecognized command '%s'\n", input)
				continue
			}
		}

		var statement internal.Statement

		switch internal.PrepareStatement(input, &statement) {
		case internal.PREPARE_SUCCESS:
			break
		case internal.PREPARE_UNRECOGNIZED_STATEMENT:
			fmt.Printf("Unrecognized keyword at start of '%s'.\n", input)
			continue
		}

		internal.ExecuteStatement(&statement)
		fmt.Println("Executed.")
	}
}
