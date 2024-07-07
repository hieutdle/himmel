#include <DB.hpp>
#include <Statement.hpp>
#include <Tuple.hpp>

#include <iostream>

void DB::print_prompt() { std::cout << "db > "; }

bool DB::parse_meta_command(std::string &command) {
  if (command[0] == '.') {
    switch (do_meta_command(command)) {
    case META_COMMAND_SUCCESS:
      return true;
    case META_COMMAND_UNRECOGNIZED_COMMAND:
      std::cout << "Unrecognized command: " << command << std::endl;
      return true;
    }
  }
  return false;
}

MetaCommandResult DB::do_meta_command(std::string &command) {
  if (command == ".exit") {
    std::cout << "Bye!" << std::endl;
    exit(EXIT_SUCCESS);
  }
  return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult DB::prepare_statement(std::string &input_line,
                                    Statement &statement) {
  if (input_line.compare(0, 6, "INSERT") == 0) {
    statement.type = STATEMENT_INSERT;
    int args_assigned = std::sscanf(
        input_line.c_str(), "INSERT %d %s %s", &(statement.tuple_to_insert.id),
        statement.tuple_to_insert.username, statement.tuple_to_insert.email);
    if (args_assigned < 3) {
      return PREPARE_SYNTAX_ERROR;
    }
    return PREPARE_SUCCESS;
  } else if (input_line.compare(0, 6, "SELECT") == 0) {
    statement.type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  } else {
    return PREPARE_UNRECOGNIZED_STATEMENT;
  }
}

bool DB::parse_statement(std::string &input_line, Statement &statement) {
  switch (prepare_statement(input_line, statement)) {
  case PREPARE_SUCCESS:
    return false;
  case PREPARE_SYNTAX_ERROR:
    std::cout << "Syntax error. Could not parse statement." << std::endl;
    return true;
  case PREPARE_UNRECOGNIZED_STATEMENT:
    std::cout << "Unrecognized keyword at start of '" << input_line << "'."
              << std::endl;
    return true;
  }
  return false;
}

void DB::execute_statement(Statement &statement, Table &table) {
  ExecuteResult result;
  switch (statement.type) {
  case STATEMENT_INSERT:
    result = execute_insert(statement, table);
    break;
  case STATEMENT_SELECT:
    result = execute_select(statement, table);
    break;
  }

  switch (result) {
  case EXECUTE_SUCCESS:
    std::cout << "Executed." << std::endl;
    break;
  case EXECUTE_TABLE_FULL:
    std::cout << "Error: Table full." << std::endl;
    break;
  }
}

ExecuteResult DB::execute_insert(Statement &statement, Table &table) {
  if (table.num_tuples >= TABLE_MAX_TUPLES) {
    std::cout << "Error: Table full." << std::endl;
    return EXECUTE_TABLE_FULL;
  }

  void *page = tuple_slot(table, table.num_tuples);
  serialize_tuple(statement.tuple_to_insert, page);
  table.num_tuples++;

  return EXECUTE_SUCCESS;
}

ExecuteResult DB::execute_select(Statement &statement, Table &table) {
  for (uint32_t i = 0; i < table.num_tuples; i++) {
    Tuple tuple;
    void *page = tuple_slot(table, i);
    deserialize_tuple(page, tuple);
    std::cout << "(" << tuple.id << ", " << tuple.username << ", "
              << tuple.email << ")" << std::endl;
  }

  return EXECUTE_SUCCESS;
}

void DB::run() {
  Table table;

  while (true) {
    print_prompt();

    std::string input_line;
    std::getline(std::cin, input_line);

    if (parse_meta_command(input_line)) {
      continue;
    }

    Statement statement;

    if (parse_statement(input_line, statement)) {
      continue;
    }

    execute_statement(statement, table);
  }
}
