#ifndef GRAPICAR__ACCESSOR_H_
#define GRAPICAR__ACCESSOR_H_

#include <cstdint>
#include <string>
#include <vector>

//struct AccessorSparseValues {
//  std::int32_t buffer_view_;
//  std::int32_t byte_offset_;
//};
//
//struct AccessorSparseIndices {
//  std::int32_t buffer_view_;
//  std::int32_t byte_offset_;
//  std::int32_t component_type_;
//};
//
//struct AccessorSparse {
//  std::int32_t count_;
//  AccessorSparseIndices indices_;
//  AccessorSparseValues values_;
//};

struct Accessor {
  std::int32_t buffer_view_;
  std::int32_t byte_offset_;
  std::int32_t component_type_;
  bool normalized_;
  std::int32_t count_;
  std::string type_;
  std::vector<float> max_; //Number assumed to be a float
  std::vector<float> min_; //Number assumed to be a float
//  AccessorSparse sparse_;
  std::string name_;
};

#endif //GRAPICAR__ACCESSOR_H_
