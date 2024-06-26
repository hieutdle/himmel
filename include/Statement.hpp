#ifndef STATEMENT_H
#define STATEMENT_H

enum StatementType { STATEMENT_INSERT, STATEMENT_SELECT };

class Statement {
public:
  StatementType type;
};

#endif // STATEMENT_H
