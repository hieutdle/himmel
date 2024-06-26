#include <Database.hpp>
#include <Statement.hpp>

#include <iostream>

void Database::printPrompt() { std::cout << "db > "; }

bool Database::parseMetaCommand(std::string &command) {
  if (command[0] == '.') {
    switch (doMetaCommand(command)) {
    case META_COMMAND_SUCCESS:
      return true;
    case META_COMMAND_UNRECOGNIZED_COMMAND:
      std::cout << "Unrecognized command: " << command << std::endl;
      return true;
    }
  }
  return false;
}

MetaCommandResult Database::doMetaCommand(std::string &command) {
  if (command == ".exit") {
    std::cout << "Bye!" << std::endl;
    exit(EXIT_SUCCESS);
  }
  return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult Database::prepareStatement(std::string &input_line,
                                         Statement &statement) {
  if (input_line.compare(0, 6, "insert") == 0) {
    statement.type = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  } else if (input_line.compare(0, 6, "select") == 0) {
    statement.type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }
  return PREPARE_UNRECOGNIZED_STATEMENT;
}

bool Database::parseStatement(std::string &input_line, Statement &statement) {
  switch (prepareStatement(input_line, statement)) {
  case PREPARE_SUCCESS:
    return false;
  case PREPARE_UNRECOGNIZED_STATEMENT:
    std::cout << "Unrecognized keyword at start of '" << input_line << "'."
              << std::endl;
    return true;
  }
  return false;
}

void Database::executeStatement(Statement &statement) {
  switch (statement.type) {
  case STATEMENT_INSERT:
    std::cout << "Executing insert statement" << std::endl;
    break;
  case STATEMENT_SELECT:
    std::cout << "Executing select statement" << std::endl;
    break;
  }
}

void Database::run() {
  while (true) {
    printPrompt();

    std::string input_line;
    std::getline(std::cin, input_line);

    if (parseMetaCommand(input_line)) {
      continue;
    }

    Statement statement;

    if (parseStatement(input_line, statement)) {
      continue;
    }

    executeStatement(statement);
  }
}
