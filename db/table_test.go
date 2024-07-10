package db

import (
	"fmt"
	"strings"
	"testing"

	"github.com/hieutdle/himmel/tools"
	"github.com/stretchr/testify/assert"
)

func TestExecuteInsert(t *testing.T) {
	table := Table{}
	statement := Statement{
		statementType: StatementInsert,
		tupleToInsert: Tuple{ID: 0, Username: "user", Email: "email"},
	}

	result := table.ExecuteInsert(&statement)
	assert.Equal(t, ExecuteSuccess, result)
	assert.Len(t, table.tuples, 1)
	assert.Equal(t, statement.tupleToInsert, table.tuples[0])
}

func TestExecuteSelect(t *testing.T) {
	table := Table{
		tuples: []Tuple{
			{ID: 0, Username: "user0", Email: "email0"},
			{ID: 1, Username: "user1", Email: "email1"},
		},
	}

	statement := Statement{statementType: StatementSelect}

	output := tools.CaptureOutput(func() {
		table.ExecuteSelect(&statement)
	})
	expectedOutput := "(0, user0, email0)\n(1, user1, email1)\n"
	assert.Equal(t, expectedOutput, output)
}

func TestExecuteSelectTableFull(t *testing.T) {
	table := Table{}
	for i := 0; i < TableMaxTuple; i++ {
		statement := Statement{
			statementType: StatementInsert,
			tupleToInsert: Tuple{ID: uint(i), Username: fmt.Sprintf("user%d", i), Email: fmt.Sprintf("email%d", i)},
		}
		result := table.ExecuteInsert(&statement)
		assert.Equal(t, ExecuteSuccess, result)
	}

	// Attempt to insert one more tuple to ensure the table is full
	statement := Statement{
		statementType: StatementInsert,
		tupleToInsert: Tuple{ID: TableMaxTuple + 1, Username: fmt.Sprintf("user%d", TableMaxTuple+1), Email: fmt.Sprintf("email%d", TableMaxTuple+1)},
	}
	result := table.ExecuteInsert(&statement)
	assert.Equal(t, ExecuteTableFull, result)

	// Select and verify the contents of the table
	selectStatement := Statement{statementType: StatementSelect}

	output := tools.CaptureOutput(func() {
		table.ExecuteSelect(&selectStatement)
	})

	var expectedOutput strings.Builder
	for i := 0; i < TableMaxTuple; i++ {
		expectedOutput.WriteString(fmt.Sprintf("(%d, user%d, email%d)\n", i, i, i))
	}

	assert.Equal(t, expectedOutput.String(), output)
}
