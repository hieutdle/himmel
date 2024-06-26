#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <Tuple.hpp>

enum StatementType { STATEMENT_INSERT, STATEMENT_SELECT };

class Statement {
public:
  StatementType type;
  Tuple tuple_to_insert;
};

#endif // STATEMENT_HPP
