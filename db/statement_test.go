package db

import (
	"fmt"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestPrepareStatement(t *testing.T) {
	tests := []struct {
		input    string
		expected PrepareResult
	}{
		{"INSERT 1 user email", PrepareSucess},
		{"insert 1 user", PrepareSyntaxError},
		{"select", PrepareSucess},
		{"unknown", PrepareUnrecognizedStatement},
	}

	for _, test := range tests {
		var statement Statement
		result := statement.PrepareStatement(test.input)
		assert.Equal(t, test.expected, result, fmt.Sprintf("for input '%s'", test.input))
	}
}

func TestParseStatement(t *testing.T) {
	tests := []struct {
		input    string
		expected bool
	}{
		{"INSERT 1 user email", false},
		{"insert 1 user", true},
		{"select", false},
		{"unknown", true},
	}

	for _, test := range tests {
		var statement Statement
		result := statement.ParseStatement(test.input)
		assert.Equal(t, test.expected, result, fmt.Sprintf("for input '%s'", test.input))
	}
}
