package db

import (
	"fmt"
	"strconv"
	"strings"
)

type PrepareResult int

const (
	PrepareSucess PrepareResult = iota
	PrepareSyntaxError
	PrepareNegativeId
	PrepareStringTooLong
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
	input = strings.ToLower(input[:6]) + input[6:]
	if len(input) >= 6 && input[:6] == "insert" {
		return statement.PrepareInsert(input)
	}
	if len(input) >= 6 && input[:6] == "select" {
		statement.statementType = StatementSelect
		return PrepareSucess
	}
	return PrepareUnrecognizedStatement
}

func (statement *Statement) PrepareInsert(input string) PrepareResult {
	statement.statementType = StatementInsert
	assigned := strings.Split(input, " ")
	if len(assigned) < 4 {
		return PrepareSyntaxError
	}
	idStr, username, email := assigned[1], assigned[2], assigned[3]
	idInt, err := strconv.Atoi(idStr)
	if err != nil {
		return PrepareSyntaxError
	}
	if idInt < 0 {
		return PrepareNegativeId
	}
	id := uint(idInt)
	if len(username) > ColumnUserSize {
		return PrepareStringTooLong
	}
	if len(email) > ColumnEmailSize {
		return PrepareStringTooLong
	}
	statement.tupleToInsert = Tuple{
		ID:       id,
		Username: username,
		Email:    email,
	}
	return PrepareSucess
}

func (statement *Statement) ParseStatement(input string) bool {
	switch statement.PrepareStatement(input) {
	case PrepareSucess:
		return false
	case PrepareNegativeId:
		fmt.Println("ID must be positive")
		return true
	case PrepareStringTooLong:
		fmt.Println("String is too long.")
		return true
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
