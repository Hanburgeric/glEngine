#ifndef GRAPICAR__BUFFER_VIEW_H_
#define GRAPICAR__BUFFER_VIEW_H_

#include <cstdint>
#include <string>

struct BufferView {
  std::int32_t buffer_;
  std::int32_t byte_offset_;
  std::int32_t byte_length_;
  std::int32_t byte_stride_;
  std::int32_t target_;
  std::string name_;
};

#endif //GRAPICAR__BUFFER_VIEW_H_
