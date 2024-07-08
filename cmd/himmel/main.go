package main

import (
	"fmt"

	"github.com/hieutdle/himmel/db"
)

func main() {
	table := db.Table{}

	for {
		db.PrintPrompt()
		input := db.ReadInput()

		if db.ParseMetaCommand(input) {
			continue
		}

		var statement db.Statement

		if statement.ParseStatement(input) {
			continue
		}
		statement.ExecuteStatement(&table)
		fmt.Println("Executed.")
	}
}
