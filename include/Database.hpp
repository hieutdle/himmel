#ifndef DATABASE_H
#define DATABASE_H

#include <Statement.hpp>
#include <string>

enum MetaCommandResult {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
};

enum PrepareResult { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT };

class Database {
public:
  void run();
  void printPrompt();

  bool parseMetaCommand(std::string &command);
  MetaCommandResult doMetaCommand(std::string &command);
  PrepareResult prepareStatement(std::string &input_line, Statement &statement);
  bool parseStatement(std::string &input_line, Statement &statement);
  void executeStatement(Statement &statement);
};

#endif // DATABASE_H
