#ifndef GRAPICAR__IMAGE_H_
#define GRAPICAR__IMAGE_H_

#include <cstdint>
#include <string>
#include <vector>

struct Image {
  std::string uri_; //String assumed to be an external file
  std::string mime_type_;
  std::int32_t buffer_view_;
  std::string name_;

  std::vector<uint8_t> data_;
};

#endif //GRAPICAR__IMAGE_H_
