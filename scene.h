#ifndef GRAPICAR__SCENE_H_
#define GRAPICAR__SCENE_H_

#include <cstdint>
#include <string>
#include <vector>

struct Scene {
  std::vector<std::int32_t> nodes_;
  std::string name_;
};

#endif //GRAPICAR__SCENE_H_
