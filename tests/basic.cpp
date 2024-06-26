#include <cstdio>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Execute a shell command and capture its output
std::string executeCommand(const char *cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

class DatabaseTest : public ::testing::Test {};

TEST_F(DatabaseTest, TestExitAndUnrecognizedCommandAndSqlSentence) {
  std::string result =
      executeCommand("echo -e 'hello world\n.HELLO WORLD\n.exit' | ./Himmel");
  std::vector<std::string> expected = {
      "db > Unrecognized keyword at start of 'hello world'.",
      "db > Unrecognized command: .HELLO WORLD", "db > Bye!"};

  std::istringstream iss(result);
  std::string line;
  size_t line_index = 0;
  while (std::getline(iss, line)) {
    ASSERT_EQ(line, expected[line_index++])
        << "Mismatch at line " << line_index;
  }
}

TEST_F(DatabaseTest, InsertsAndRetrievesARow) {
  std::string result =
      executeCommand("echo -e 'INSERT 1 user1 person1@example.com\nINSERT 2 "
                     "user2\nSELECT\n.exit' | ./Himmel");
  std::vector<std::string> expected = {
      "db > Executed.", "db > Syntax error. Could not parse statement.",
      "db > (1, user1, person1@example.com)", "Executed.", "db > Bye!"};

  std::istringstream iss(result);
  std::string line;
  size_t line_index = 0;
  while (std::getline(iss, line)) {
    ASSERT_EQ(line, expected[line_index++])
        << "Mismatch at line " << line_index;
  }
}
