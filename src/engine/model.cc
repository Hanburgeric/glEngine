#include "model.h"

// System headers
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

// Vendor headers
#include "glad/gl.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "nlohmann/json.hpp"

// User headers
#include "importer.h"
#include "../gltf/accessor.h"
#include "../gltf/buffer.h"
#include "../gltf/buffer_view.h"
#include "../gltf/gltf.h"
#include "../gltf/mesh.h"
#include "../gltf/node.h"
#include "../gltf/scene.h"
#include "utils.h"

namespace glEngine {
Model::Model(const std::string& file_path) {
  ImportModelFromFile(file_path);
}

void Model::Render(renderer::Program& program) const {
  // Get default scene
  if (gltf_.scene_.has_value()) {
    int scene = gltf_.scene_.value();

    // Get nodes from default scene
    const auto &nodes = gltf_.scenes_[scene].nodes_;

    // Iterate through nodes
    for (int node : nodes) {
      // Render
      RenderNode(program, gltf_.nodes_[node], glm::mat4(1.0F));
    }
  }
}

void Model::ImportModelFromFile(const std::string& file_path) {
  // Open glTF file
  std::ifstream file(file_path);

  if (!file) {
    std::cerr << "Failed to open glTF file at " << file_path << std::endl;
    return;
  }

  // Clear previous contents of model
  Clear();

  // Cache file path
  file_path_ = file_path;

  // Cache JSON data
  json_ = nlohmann::json::parse(file);

  // Cache glTF data
  gltf_ = glEngine::importer::ImportGltfFromJson(json_);

  // Initialize
  Initialize();
}

const gltf::Gltf& Model::GetGltf() const {
  return gltf_;
}

void Model::Initialize() {
  // Buffers
  for (auto& buffer : gltf_.buffers_) {
    // Store URI as binary data
    if (!buffer.uri_.empty()) {
      // Embedded data
      if (glEngine::utils::IsUriEmbedded(buffer.uri_)) {
        // TO-DO : decode embedded data
        std::cerr << "embedded URIs have not yet been implemented" << std::endl;
      }

      // External file
      else {
        std::filesystem::path path(file_path_);
        std::ifstream binary_data(path.parent_path().string() + "/" + buffer.uri_, std::ios::binary);
        buffer.data_ = std::vector<unsigned char>(std::istreambuf_iterator<char>(binary_data), {});
      }
    }

    // GLB-stored buffers
    else {
      // TO-DO : account for GLB-stored buffers
      std::cerr << "GLB-stored buffers have not yet been implemented" << std::endl;
    }
  }

  // Meshes
  for (auto& mesh : gltf_.meshes_) {
    // Primitives
    for (auto& primitive : mesh.primitives_) {
      // VAO
      glGenVertexArrays(1, &primitive.vao_);
      glBindVertexArray(primitive.vao_);

      // VBOs
      for (const auto& attribute : primitive.attributes_) {
        unsigned int vbo;

        const auto& accessor = gltf_.accessors_[attribute.second];
        if (accessor.buffer_view_.has_value()) {
          const auto& buffer_view = gltf_.buffer_views_[accessor.buffer_view_.value()];
          const auto& buffer = gltf_.buffers_[buffer_view.buffer_];

          if (!buffer.uri_.empty()) {
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            int accessor_byte_offset = accessor.byte_offset_.value_or(0);
            int buffer_view_byte_offset = buffer_view.byte_offset_.value_or(0);
            glBufferData(GL_ARRAY_BUFFER,
                         buffer_view.byte_length_,
                         &buffer.data_[accessor_byte_offset + buffer_view_byte_offset],
                         GL_STATIC_DRAW);

            // TO-DO : automatically match attribute locations with those of the relevant shader
            // TO-DO : validate VertexAttrib stride and other stuff...
            unsigned int index = primitive.vbos_.size();
            int size = glEngine::utils::TypeToNumComponents(accessor.type_);
            int type = accessor.component_type_;
            bool normalized = accessor.normalized_.value_or(false);
            unsigned int stride = buffer_view.byte_stride_.value_or(0);

            glVertexAttribPointer(index, size, type, normalized, stride,
                                  static_cast<char*>(nullptr) + accessor_byte_offset);
            glEnableVertexAttribArray(index);
          } else {
            // TO-DO : a buffer MAY have an undefined uri property
            std::cerr << "undefined behavior : a buffer does not have the \"uri\" property" << std::endl;
          }

        } else {
          // TO-DO : an accessor MAY have an undefined bufferView property
          std::cerr << "undefined behavior : an accessor does not have the \"bufferView\" property" << std::endl;
        }

        primitive.vbos_.push_back(vbo);
      }

      // IBO
      if (primitive.indices_.has_value()) {
        unsigned int ibo;

        const auto& accessor = gltf_.accessors_[primitive.indices_.value()];
        if (accessor.buffer_view_.has_value()) {
          const auto& buffer_view = gltf_.buffer_views_[accessor.buffer_view_.value()];
          const auto& buffer = gltf_.buffers_[buffer_view.buffer_];

          if (!buffer.uri_.empty()) {
            glGenBuffers(1, &primitive.ibo_);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitive.ibo_);

            int accessor_byte_offset = accessor.byte_offset_.value_or(0);
            int buffer_view_byte_offset = buffer_view.byte_offset_.value_or(0);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         buffer_view.byte_length_,
                         &buffer.data_[accessor_byte_offset + buffer_view_byte_offset],
                         GL_STATIC_DRAW);
          } else {
            // TO-DO : a buffer MAY have an undefined uri property
            std::cerr << "undefined behavior : a buffer does not have the \"uri\" property" << std::endl;
          }

        } else {
          // TO-DO : an accessor MAY have an undefined bufferView property
          std::cerr << "undefined behavior : an accessor does not have the \"bufferView\" property" << std::endl;
        }
      }
    }
  }
}

void Model::Clear() {
  // Clear file path
  file_path_.clear();

  // Clear JSON data
  json_.clear();

  // Clear glTF data
  gltf_.accessors_.clear();
  gltf_.buffers_.clear();
  gltf_.buffer_views_.clear();

  for (auto& mesh : gltf_.meshes_) {
    for (auto& primitive : mesh.primitives_) {
      glDeleteBuffers(1, &primitive.ibo_);
      glDeleteBuffers(primitive.vbos_.size(), &primitive.vbos_[0U]);
      glDeleteVertexArrays(1, &primitive.vao_);
    }
  }
  gltf_.meshes_.clear();

  gltf_.nodes_.clear();
  gltf_.scene_.reset();
  gltf_.scenes_.clear();
}

void Model::RenderNode(renderer::Program& program, const gltf::Node& node, const glm::mat4x4& TRS) const {
  // Obtain transformation matrix
  glm::mat4 matrix;
  if (node.matrix_.has_value()) {
    for (int r = 0; r < 4; r++) {
      for (int c = 0; c < 4; c++) {
        matrix[r][c] = node.matrix_.value()[4 * r + c];
      }
    }
  } else {
    matrix = glm::mat4(1.0F);

    // Scale
    if (node.scale_.has_value()) {
      glm::vec3 scale(node.scale_.value()[0U],
                      node.scale_.value()[1U],
                      node.scale_.value()[2U]);
      matrix = glm::scale(matrix, scale);
    }

    // Rotation
    glm::quat rotation;
    if (node.rotation_.has_value()) {
      glm::quat rotation(node.rotation_.value()[3U],
                         node.rotation_.value()[0U],
                         node.rotation_.value()[1U],
                         node.rotation_.value()[2U]);
      matrix *= glm::mat4_cast(rotation);
    }

    // Translation
    if (node.translation_.has_value()) {
      glm::vec3 translation(node.translation_.value()[0U],
                            node.translation_.value()[1U],
                            node.translation_.value()[2U]);
      matrix = glm::translate(matrix, translation);
    }
  }

  // Model matrix
  glm::mat4 M(TRS * matrix);

  // Render children nodes
  for (const auto& child : node.children_) {
    RenderNode(program, gltf_.nodes_[child], M);
  }

  // Render
  glUniformMatrix4fv(program.GetUniformLocation("model"), 1, false, glm::value_ptr(M));

  if (node.mesh_.has_value()) {
    int mesh_index = node.mesh_.value();
    const auto& mesh = gltf_.meshes_[mesh_index];

    // Mesh primitive
    for (const auto& mesh_primitive : mesh.primitives_) {
      // Bind VAO
      glBindVertexArray(mesh_primitive.vao_);

      // Render indexed geometry
      if (mesh_primitive.indices_.has_value()) {
        const auto& accessor = gltf_.accessors_[mesh_primitive.indices_.value()];

        glDrawElements(mesh_primitive.mode_.value_or(4),
                       accessor.count_,
                       accessor.component_type_,
                       static_cast<char*>(nullptr) + accessor.byte_offset_.value_or(0));
      }

      // Render non-indexed geometry
      else {
        const auto& accessor = gltf_.accessors_[mesh_primitive.attributes_.at("POSITION")];
        glDrawArrays(mesh_primitive.mode_.value_or(4), 0, accessor.count_);
      }
    }
  }
}
}
