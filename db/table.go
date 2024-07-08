package db

import "fmt"

const tableMaxTuple = 100

type Tuple struct {
	ID       uint
	Username string
	Email    string
}

type Table struct {
	tuples []Tuple
}

type ExecuteResult int

const (
	ExecuteSuccess ExecuteResult = iota
	ExecuteTableFull
)

func (table *Table) ExecuteInsert(statement *Statement) ExecuteResult {
	if len(table.tuples) >= tableMaxTuple {
		fmt.Println("Error: Table full.")
		return ExecuteTableFull
	}
	table.tuples = append(table.tuples, statement.tupleToInsert)
	return ExecuteSuccess
}

func (table *Table) ExecuteSelect(statement *Statement) ExecuteResult {
	for _, row := range table.tuples {
		printRow(&row)
	}
	return ExecuteSuccess
}

func printRow(tuple *Tuple) {
	fmt.Printf("(%d, %s, %s)\n", tuple.ID, tuple.Username, tuple.Email)
}
