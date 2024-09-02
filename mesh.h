#ifndef GRAPICAR__MESH_H_
#define GRAPICAR__MESH_H_

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

struct MeshPrimitive {
  std::unordered_map<std::string, std::int32_t> attributes_;
  std::int32_t indices_;
  std::int32_t material_;
  std::int32_t mode_;
  std::vector<std::unordered_map<std::string, std::int32_t>> targets_;

  std::uint32_t vao_;
  std::vector<std::uint32_t> vbos_;
  std::uint32_t ebo_;
};

struct Mesh {
  std::vector<MeshPrimitive> primitives_;
  std::vector<float> weights_; //Number assumed to be a float
  std::string name_;
};

#endif //GRAPICAR__MESH_H_
