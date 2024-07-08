package tools

import (
	"io"
	"os"
)

func CaptureOutput(f func()) string {
	r, w, _ := os.Pipe()
	oldStdout := os.Stdout
	os.Stdout = w

	f()

	w.Close()
	os.Stdout = oldStdout
	out, _ := io.ReadAll(r)

	return string(out)
}
