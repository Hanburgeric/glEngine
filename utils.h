#ifndef GRAPICAR__UTILS_H_
#define GRAPICAR__UTILS_H_

#include <cstdint>
#include <string>

#include "accessor.h"
#include "buffer_view.h"

//Accessor utility functions
std::int32_t GetByteStride(const Accessor& accessor, const BufferView& buffer_view);
std::int32_t GetComponentSizeInBytes(const std::int32_t& component_type);
std::int32_t GetNumComponentsInType(const Accessor& accessor);

//Animation utility functions
template<typename T>
T clamp(const T& t, const T& min, const T& max) {
  const T a = t < min ? min : t;
  return a > max ? max : a;
}

//Miscellaneous utility functions
std::string GetBaseDir(const std::string& path);

#endif //GRAPICAR__UTILS_H_
