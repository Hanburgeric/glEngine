#ifndef GRAPICAR__SAMPLER_H_
#define GRAPICAR__SAMPLER_H_

#include <cstdint>
#include <string>

struct Sampler {
  std::int32_t mag_filter_;
  std::int32_t min_filter_;
  std::int32_t wrap_s_;
  std::int32_t wrap_t_;
  std::string name_;
};

#endif //GRAPICAR__SAMPLER_H_
