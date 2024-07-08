package db

import "fmt"

type PrepareResult int

const (
	PrepareSucess PrepareResult = iota
	PrepareSyntaxError
	PrepareUnrecognizedStatement
)

type StatementType int

const (
	StatementInsert StatementType = iota
	StatementSelect
)

type Statement struct {
	statementType StatementType
	tupleToInsert Tuple
}

func (statement *Statement) PrepareStatement(input string) PrepareResult {
	if len(input) >= 6 && (input[:6] == "insert" || input[:6] == "INSERT") {
		statement.statementType = StatementInsert
		assigned, err := fmt.Sscanf(input, "insert %d %s %s", &statement.tupleToInsert.ID, &statement.tupleToInsert.Username, &statement.tupleToInsert.Email)
		if assigned < 3 || err != nil {
			return PrepareSyntaxError
		}
		return PrepareSucess
	}
	if len(input) >= 6 && (input[:6] == "select" || input[:6] == "SELECT") {
		statement.statementType = StatementSelect
		return PrepareSucess
	}
	return PrepareUnrecognizedStatement
}

func (statement *Statement) ParseStatement(input string) bool {
	switch statement.PrepareStatement(input) {
	case PrepareSucess:
		return false
	case PrepareSyntaxError:
		fmt.Println("Syntax error. Could not parse statement.")
		return true
	case PrepareUnrecognizedStatement:
		fmt.Printf("Unrecognized keyword at start of '%s'.\n", input)
		return true
	}
	return false
}
func (statement *Statement) ExecuteStatement(table *Table) ExecuteResult {
	switch statement.statementType {
	case StatementInsert:
		return table.ExecuteInsert(statement)
	case StatementSelect:
		return table.ExecuteSelect(statement)
	}
	return ExecuteSuccess
}
