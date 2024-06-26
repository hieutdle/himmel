#include <cstdio>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string run_script(const std::vector<std::string> &commands) {
  std::string tempFileName =
      std::filesystem::temp_directory_path() / "script.tmp";
  std::ofstream tempFile(tempFileName);
  if (!tempFile) {
    throw std::runtime_error("Failed to create temporary script file.");
  }

  for (const auto &cmd : commands) {
    tempFile << cmd << '\n';
  }
  tempFile.close();

  std::string command = "./Himmel < " + tempFileName;
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("Failed to run Himmel executable.");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get())) {
    result += buffer.data();
  }

  std::filesystem::remove(tempFileName);
  return result;
}

class DatabaseTest : public ::testing::Test {};

// Tests for unrecognized commands and proper exit behavior
TEST_F(DatabaseTest, ExitAndUnrecognizedCommandAndSqlSentence) {
  std::vector<std::string> commands = {"hello world", ".HELLO WORLD", ".exit"};
  std::string result = run_script(commands);
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

// Tests inserting data and retrieving a row
TEST_F(DatabaseTest, InsertsAndRetrievesATuple) {
  std::vector<std::string> commands = {"INSERT 1 user1 person1@example.com",
                                       "INSERT 2 user2", "SELECT", ".exit"};
  std::string result = run_script(commands);
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
