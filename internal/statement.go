package internal

import "fmt"

type PrepareResult int

const (
	PREPARE_SUCCESS PrepareResult = iota
	PREPARE_UNRECOGNIZED_STATEMENT
)

type StatementType int

const (
	STATEMENT_INSERT StatementType = iota
	STATEMENT_SELECT
)

type Statement struct {
	statementType StatementType
}

func PrepareStatement(input string, statement *Statement) PrepareResult {
	if len(input) >= 6 && input[:6] == "insert" {
		statement.statementType = STATEMENT_INSERT
		return PREPARE_SUCCESS
	}
	if input == "SELECT" || input == "select" {
		statement.statementType = STATEMENT_SELECT
		return PREPARE_SUCCESS
	}
	return PREPARE_UNRECOGNIZED_STATEMENT
}

func ExecuteStatement(statement *Statement) {
	switch statement.statementType {
	case STATEMENT_INSERT:
		fmt.Println("This is where we would do an insert.")
	case STATEMENT_SELECT:
		fmt.Println("This is where we would do a select.")
	}
}
