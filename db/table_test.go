package db

import (
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
			{ID: 0, Username: "user1", Email: "email1"},
			{ID: 1, Username: "user2", Email: "email2"},
		},
	}

	statement := Statement{statementType: StatementSelect}

	output := tools.CaptureOutput(func() {
		table.ExecuteSelect(&statement)
	})
	expectedOutput := "(0, user1, email1)\n(1, user2, email2)\n"
	assert.Equal(t, expectedOutput, output)
}
