#ifndef GRAPICAR__UTILS_H_
#define GRAPICAR__UTILS_H_

#include "accessor.h"
#include "buffer_view.h"

//Accessor utility functions
int32_t GetByteStride(const Accessor& accessor, const BufferView& buffer_view);
int32_t GetComponentSizeInBytes(const int32_t& component_type);
int32_t GetNumComponentsInType(const Accessor& accessor);

#endif //GRAPICAR__UTILS_H_
