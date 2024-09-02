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
  ImportGltf(file_path);
}

void Model::ImportGltf(const std::string& file_path) {
  // Open glTF file
  std::cout << "Opening glTF file at " << file_path << std::endl;
  std::ifstream file(file_path);

  if (!file) {
    std::cerr << "Failed to open glTF file at " << file_path << std::endl;
    return;
  }

  // Clear previous contents of model
  Clear();

  // Cache file path
  std::filesystem::path path(file_path);
  path_ = path.parent_path().string();

  // Cache JSON data
  std::cout << "Parsing file..." << std::endl;
  json_ = nlohmann::json::parse(file);

  // Cache glTF data
  // Extensions Used

  // Extensions Required

  // Accessors
  if (json_.contains("accessors")) {
    std::cout << "Importing accessors..." << std::endl;
    ImportAccessors();
  }

  // Animations

  // Asset - REQUIRED

  // Buffers
  if (json_.contains("buffers")) {
    std::cout << "Importing buffers..." << std::endl;
    ImportBuffers(file_path);
  }

  // Buffer Views
  if (json_.contains("bufferViews")) {
    std::cout << "Importing buffer views..." << std::endl;
    ImportBufferViews();
  }

  // Cameras

  // Images

  // Materials

  // Meshes
  if (json_.contains("meshes")) {
    std::cout << "Importing meshes..." << std::endl;
    ImportMeshes();
  }

  // Nodes
  if (json_.contains("nodes")) {
    std::cout << "Importing nodes..." << std::endl;
    ImportNodes();
  }

  // Samplers

  // Scene
  if (json_.contains("scene")) {
    std::cout << "Importing scene..." << std::endl;
    gltf_.scene_ = json_["scene"];
  }

  // Scenes
  if (json_.contains("scenes")) {
    std::cout << "Importing scenes..." << std::endl;
    ImportScenes();
  }

  // Skins

  // Textures

  // Extensions

  // Extras

  // Initialize
  std::cout << "Initializing model..." << std::endl;
  Initialize();
}

gltf::Gltf Model::GetGltf() const {
  return gltf_;
}

void Model::Clear() {
  // Clear file path
  path_.clear();

  // Clear JSON data
  json_.clear();

  // Clear glTF data
  gltf_.accessors_.clear();
  gltf_.buffers_.clear();
  gltf_.buffer_views_.clear();
  gltf_.meshes_.clear();
  gltf_.nodes_.clear();
  gltf_.scene_.reset();
  gltf_.scenes_.clear();
}

void Model::ImportAccessors() {
  const auto& accessors = json_["accessors"];
  for (const auto& accessor : accessors) {
    gltf::Accessor new_accessor;

    // Buffer View
    if (accessor.contains("bufferView")) {
      new_accessor.buffer_view_ = accessor["bufferView"];
    }

    // Byte Offset - DEFAULT : 0
    if (accessor.contains("byteOffset")) {
      new_accessor.byte_offset_ = accessor["byteOffset"];
    }

    // Component Type - REQUIRED
    if (accessor.contains("componentType")) {
      new_accessor.component_type_ = accessor["componentType"];
    } else {
      std::cerr << "An accessor MUST have the \"componentType\" property" << std::endl;
    }

    // Normalized - DEFAULT : false
    if (accessor.contains("normalized")) {
      new_accessor.normalized_ = accessor["normalized"];
    }

    // Count - REQUIRED
    if (accessor.contains("count")) {
      new_accessor.count_ = accessor["count"];
    } else {
      std::cerr << "An accessor MUST have the \"count\" property" << std::endl;
    }

    // Type - REQUIRED
    if (accessor.contains("type")) {
      new_accessor.type_ = accessor["type"];
    } else {
      std::cerr << "An accessor MUST have the \"type\" property" << std::endl;
    }

    // Max

    // Min

    // Sparse

    // Name
    if (accessor.contains("name")) {
      new_accessor.name_ = accessor["name"];
    }

    // Extensions

    // Extras

    gltf_.accessors_.push_back(new_accessor);
  }
}

void Model::ImportBuffers(const std::string& file_path) {
  const auto& buffers = json_["buffers"];
  for (const auto& buffer : buffers) {
    gltf::Buffer new_buffer;

    // URI
    if (buffer.contains("uri")) {
      new_buffer.uri_ = buffer["uri"];
    }

    // Byte Length - REQUIRED
    if (buffer.contains("byteLength")) {
      new_buffer.byte_length_ = buffer["byteLength"];
    } else {
      std::cerr << "A buffer MUST have the \"byteLength\" property" << std::endl;
    }

    // Name
    if (buffer.contains("name")) {
      new_buffer.name_ = buffer["name"];
    }

    // Extensions

    // Extras

    gltf_.buffers_.push_back(new_buffer);
  }
}

void Model::ImportBufferViews() {
  const auto& buffer_views = json_["bufferViews"];
  for (const auto& buffer_view : buffer_views) {
    gltf::BufferView new_buffer_view;

    // Buffer - REQUIRED
    if (buffer_view.contains("buffer")) {
      new_buffer_view.buffer_ = buffer_view["buffer"];
    } else {
      std::cerr << "A buffer view MUST have the \"buffer\" property" << std::endl;
    }

    // Byte Offset - DEFAULT : 0
    if (buffer_view.contains("byteOffset")) {
      new_buffer_view.byte_offset_ = buffer_view["byteOffset"];
    }

    // Byte Length - REQUIRED
    if (buffer_view.contains("byteLength")) {
      new_buffer_view.byte_length_ = buffer_view["byteLength"];
    } else {
      std::cerr << "A buffer view MUST have the \"byteLength\" property" << std::endl;
    }

    // Byte Stride
    if (buffer_view.contains("byteStride")) {
      new_buffer_view.byte_stride_ = buffer_view["byteStride"];
    }

    // Target
    if (buffer_view.contains("target")) {
      new_buffer_view.target_ = buffer_view["target"];
    }

    // Name
    if (buffer_view.contains("name")) {
      new_buffer_view.name_ = buffer_view["name"];
    }

    // Extensions

    // Extras

    gltf_.buffer_views_.push_back(new_buffer_view);
  }
}

void Model::ImportMeshes() {
  const auto& meshes = json_["meshes"];
  for (const auto& mesh : meshes) {
    gltf::Mesh new_mesh;

    // Primitives - REQUIRED
    if (mesh.contains("primitives")) {
      const auto& primitives = mesh["primitives"];
      for (const auto& primitive : primitives) {
        gltf::MeshPrimitive new_mesh_primitive;

        // Attributes - REQUIRED
        if (primitive.contains("attributes")) {
          const auto& attributes = primitive["attributes"];
          for (const auto& attribute : attributes.items()) {
            (void)new_mesh_primitive.attributes_.emplace(attribute.key(), attribute.value());
          }
        } else {
          std::cerr << "A mesh primitive MUST have the \"attributes\" property" << std::endl;
        }

        // Indices
        if (primitive.contains("indices")) {
          new_mesh_primitive.indices_ = primitive["indices"];
        }

        // Material
        if (primitive.contains("material")) {
          new_mesh_primitive.material_ = primitive["material"];
        }

        // Mode - DEFAULT : 4
        if (primitive.contains("mode")) {
          new_mesh_primitive.mode_ = primitive["mode"];
        }

        // Targets

        new_mesh.primitives_.push_back(new_mesh_primitive);
      }
    } else {
      std::cerr << "A mesh MUST have the \"primitives\" property" << std::endl;
    }

    // Weights

    // Name
    if (mesh.contains("name")) {
      new_mesh.name_ = mesh["name"];
    }

    gltf_.meshes_.push_back(new_mesh);
  }
}

void Model::ImportNodes() {
  const auto& nodes = json_["nodes"];
  for (const auto& node : nodes) {
    gltf::Node new_node;

    // Camera

    // Children

    // Skin

    // Matrix

    // Mesh
    if (node.contains("mesh")) {
      new_node.mesh_ = node["mesh"];
    }

    // Rotation

    // Scale

    // Translation

    // Weights

    // Name
    if (node.contains("name")) {
      new_node.name_ = node["name"];
    }

    // Extensions

    // Extras

    gltf_.nodes_.push_back(new_node);
  }
}

void Model::ImportScenes() {
  const auto& scenes = json_["scenes"];
  for (const auto& scene : scenes) {
    gltf::Scene new_scene;

    // Nodes
    if (scene.contains("nodes")) {
      const auto& nodes = scene["nodes"];
      for (const auto& node : nodes) {
        new_scene.nodes_.push_back(node);
      }
    }

    // Name
    if (scene.contains("name")) {
      new_scene.name_ = scene["name"];
    }

    // Extensions

    // Extras

    gltf_.scenes_.push_back(new_scene);
  }
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
        std::ifstream binary_data(path_ + "/" + buffer.uri_, std::ios::binary);
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
                         GL_DYNAMIC_DRAW);

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

      // EBO
      if (primitive.indices_.has_value()) {
        unsigned int ibo;

        const auto& accessor = gltf_.accessors_[primitive.indices_.value()];
        if (accessor.buffer_view_.has_value()) {
          const auto& buffer_view = gltf_.buffer_views_[accessor.buffer_view_.value()];
          const auto& buffer = gltf_.buffers_[buffer_view.buffer_];

          if (!buffer.uri_.empty()) {
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            int accessor_byte_offset = accessor.byte_offset_.value_or(0);
            int buffer_view_byte_offset = buffer_view.byte_offset_.value_or(0);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         buffer_view.byte_length_,
                         &buffer.binary_data_[accessor_byte_offset + buffer_view_byte_offset],
                         GL_DYNAMIC_DRAW);
          } else {
            // TO-DO : a buffer MAY have an undefined uri property
            std::cerr << "undefined behavior : a buffer does not have the \"uri\" property" << std::endl;
          }

        } else {
          // TO-DO : an accessor MAY have an undefined bufferView property
          std::cerr << "undefined behavior : an accessor does not have the \"bufferView\" property" << std::endl;
        }

        primitive.ibo_ = ibo;
      }
    }
  }
}
}
