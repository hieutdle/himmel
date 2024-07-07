#ifndef TABLE_HPP
#define TABLE_HPP

#include "Tuple.hpp"
#include <cstdint>

#define TABLE_MAX_PAGES 100

const uint32_t PAGE_SIZE = 4096;
const uint32_t TUPLE_PER_PAGE = PAGE_SIZE / TUPLE_SIZE;
const uint32_t TABLE_MAX_TUPLES = TUPLE_PER_PAGE * TABLE_MAX_PAGES;

class Table {
public:
  uint32_t num_tuples;
  void *pages[TABLE_MAX_PAGES]{};
  Table();
  ~Table();
};

void *tuple_slot(Table &table, uint32_t row_num);

#endif // TABLE_HPP
