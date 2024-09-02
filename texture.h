#ifndef GRAPICAR__TEXTURE_H_
#define GRAPICAR__TEXTURE_H_

#include <cstdint>
#include <string>

struct Texture {
  std::int32_t sampler_;
  std::int32_t source_;
  std::string name_;

  std::uint32_t texture_;
};

#endif //GRAPICAR__TEXTURE_H_
