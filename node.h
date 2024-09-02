#ifndef GRAPICAR__NODE_H_
#define GRAPICAR__NODE_H_

#include <array>
#include <cstdint>
#include <string>
#include <vector>

struct Node {
  std::int32_t camera_;
  std::vector<std::int32_t> children_;
  std::int32_t skin_;
  std::array<float, 16U> matrix_; //Number assumed to be a float
  std::int32_t mesh_;
  std::array<float, 4U> rotation_; //Number assumed to be a float
  std::array<float, 3U> scale_; //Number assumed to be a float
  std::array<float, 3U> translation_; //Number assumed to be a float
  std::vector<float> weights_; //Number assumed to be a float
  std::string name_;
};

#endif //GRAPICAR__NODE_H_
