#include <Tuple.hpp>
#include <cstring>

void serialize_tuple(Tuple &tuple, void *data) {
  memcpy((char *)data + ID_OFFSET, &(tuple.id), ID_SIZE);
  memcpy((char *)data + USERNAME_OFFSET, &(tuple.username), USERNAME_SIZE);
  memcpy((char *)data + EMAIL_OFFSET, &(tuple.email), EMAIL_SIZE);
}

void deserialize_tuple(void *data, Tuple &tuple) {
  memcpy(&(tuple.id), (char *)data + ID_OFFSET, ID_SIZE);
  memcpy(&(tuple.username), (char *)data + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&(tuple.email), (char *)data + EMAIL_OFFSET, EMAIL_SIZE);
}