package db

import (
	"fmt"
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestPrepareStatement(t *testing.T) {
	maxLengthUsername := strings.Repeat("a", ColumnUserSize)
	maxLengthEmail := strings.Repeat("a", ColumnEmailSize)
	tooLongUsername := strings.Repeat("a", ColumnUserSize+1)
	tooLongEmail := strings.Repeat("a", ColumnEmailSize+1)

	tests := []struct {
		input    string
		expected PrepareResult
	}{
		{"INSERT 0 user email", PrepareSucess},
		{"insert 1 user", PrepareSyntaxError},
		{"select", PrepareSucess},
		{"unknown", PrepareUnrecognizedStatement},
		{fmt.Sprintf("insert 1 %s %s", maxLengthUsername, maxLengthEmail), PrepareSucess},
		{fmt.Sprintf("insert 1 %s %s", tooLongUsername, maxLengthEmail), PrepareStringTooLong},
		{fmt.Sprintf("insert 1 %s %s", maxLengthUsername, tooLongEmail), PrepareStringTooLong},
		{"insert -1 user email", PrepareNegativeId},
	}

	for _, test := range tests {
		var statement Statement
		result := statement.PrepareStatement(test.input)
		assert.Equal(t, test.expected, result, fmt.Sprintf("for input '%s'", test.input))
	}
}

func TestParseStatement(t *testing.T) {
	maxLengthUsername := strings.Repeat("a", ColumnUserSize)
	maxLengthEmail := strings.Repeat("a", ColumnEmailSize)
	tooLongUsername := strings.Repeat("a", ColumnUserSize+1)
	tooLongEmail := strings.Repeat("a", ColumnEmailSize+1)

	tests := []struct {
		input    string
		expected bool
	}{
		{"INSERT 0 user email", false},
		{"insert 1 user", true},
		{"select", false},
		{"unknown", true},
		{fmt.Sprintf("insert 1 %s %s", maxLengthUsername, maxLengthEmail), false},
		{fmt.Sprintf("insert 1 %s %s", tooLongUsername, maxLengthEmail), true},
		{fmt.Sprintf("insert 1 %s %s", maxLengthUsername, tooLongEmail), true},
		{"insert -1 user email", true},
	}

	for _, test := range tests {
		var statement Statement
		result := statement.ParseStatement(test.input)
		assert.Equal(t, test.expected, result, fmt.Sprintf("for input '%s'", test.input))
	}
}
