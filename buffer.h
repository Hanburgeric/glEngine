#ifndef GRAPICAR__BUFFER_H_
#define GRAPICAR__BUFFER_H_

#include <cstdint>
#include <string>
#include <vector>

struct Buffer {
  std::string uri_; //String assumed to be an external file
  std::int32_t byte_length_;
  std::string name_;

  std::vector<char> data_;
};

#endif //GRAPICAR__BUFFER_H_
