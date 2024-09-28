#include "model.h"

// System headers
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

// Vendor headers
#include "glad/gl.h"
#include "nlohmann/json.hpp"

// User headers
#include "engine/importer.h"
#include "gltf/accessor.h"
#include "gltf/buffer.h"
#include "gltf/buffer_view.h"
#include "gltf/gltf.h"
#include "gltf/mesh.h"
#include "gltf/node.h"
#include "gltf/scene.h"
#include "utils.h"

namespace glEngine {
Model::Model(const std::string& file_path) {
  ImportModelFromFile(file_path);
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
        buffer.binary_data_ = std::vector<unsigned char>(std::istreambuf_iterator<char>(binary_data), {});
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
                         &buffer.binary_data_[accessor_byte_offset + buffer_view_byte_offset],
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
                         &buffer.binary_data_[accessor_byte_offset + buffer_view_byte_offset],
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
}
