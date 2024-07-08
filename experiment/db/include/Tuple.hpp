#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <cstdint>

// #define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

enum class ColumnName { id, username, email };

struct Tuple {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE];
  char email[COLUMN_EMAIL_SIZE];
};

constexpr uint32_t ID_SIZE = sizeof(Tuple::id);
constexpr uint32_t USERNAME_SIZE = sizeof(Tuple::username);
constexpr uint32_t EMAIL_SIZE = sizeof(Tuple::email);
constexpr uint32_t ID_OFFSET = 0;
constexpr uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
constexpr uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
constexpr uint32_t TUPLE_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void serialize_tuple(Tuple &tuple, void *data);
void deserialize_tuple(void *data, Tuple &tuple);

#endif // TUPLE_HPP
