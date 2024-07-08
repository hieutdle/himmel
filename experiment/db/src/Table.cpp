#include <Table.hpp>
#include <cstddef>
#include <cstdlib>

Table::Table() {
  num_tuples = 0;
  for (auto & page : pages) {
    page = nullptr;
  }
}

Table::~Table() {
  for (int i = 0; pages[i]; i++) {
    free(pages[i]);
  }
}

void *tuple_slot(Table &table, uint32_t tuple_num) {
  uint32_t page_num = tuple_num / TUPLE_PER_PAGE;
  void *page = table.pages[page_num];
  if (page == nullptr) {
    // Allocate memory only when we try to access page
    page = table.pages[page_num] = malloc(PAGE_SIZE);
  }
  uint32_t row_offset = tuple_num % TUPLE_PER_PAGE;
  uint32_t byte_offset = row_offset * TUPLE_SIZE;
  return (char *)page + byte_offset;
}