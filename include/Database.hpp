#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "Table.hpp"
#include <Statement.hpp>
#include <string>

enum MetaCommandResult {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
};

enum PrepareResult {
  PREPARE_SUCCESS,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT
};

enum ExecuteResult { EXECUTE_SUCCESS, EXECUTE_TABLE_FULL };

class Database {
public:
  void run();
  void print_prompt();

  bool parse_meta_command(std::string &command);
  MetaCommandResult do_meta_command(std::string &command);

  PrepareResult prepare_statement(std::string &input_line,
                                  Statement &statement);
  bool parse_statement(std::string &input_line, Statement &statement);
  void execute_statement(Statement &statement, Table &table);
  ExecuteResult execute_insert(Statement &statement, Table &table);
  ExecuteResult execute_select(Statement &statement, Table &table);
};

#endif // DATABASE_HPP
