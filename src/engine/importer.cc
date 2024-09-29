#include "importer.h"

// System headers
#include <iostream>

// Vendor headers
#include "nlohmann/json.hpp"

// User headers
#include "../gltf/accessor.h"
#include "../gltf/buffer.h"
#include "../gltf/buffer_view.h"
#include "../gltf/gltf.h"
#include "../gltf/mesh.h"
#include "../gltf/node.h"
#include "../gltf/scene.h"

namespace glEngine::importer {
gltf::Gltf ImportGltfFromJson(const nlohmann::json& json) {
  gltf::Gltf new_gltf;

  // Extensions Used

  // Extensions Required

  // Accessors
  if (json.contains("accessors")) {
    const auto& accessors = json["accessors"];
    for (const auto &accessor : accessors) {
      new_gltf.accessors_.push_back(ImportAccessor(accessor));
    }
  }

  // Animations

  // Asset - REQUIRED

  // Buffers
  if (json.contains("buffers")) {
    const auto& buffers = json["buffers"];
    for (const auto& buffer : buffers) {
      new_gltf.buffers_.push_back(ImportBuffer(buffer));
    }
  }

  // Buffer Views
  if (json.contains("bufferViews")) {
    const auto& buffer_views = json["bufferViews"];
    for (const auto& buffer_view : buffer_views) {
      new_gltf.buffer_views_.push_back(ImportBufferView(buffer_view));
    }
  }

  // Cameras

  // Images

  // Materials

  // Meshes
  if (json.contains("meshes")) {
    const auto& meshes = json["meshes"];
    for (const auto& mesh : meshes) {
      new_gltf.meshes_.push_back(ImportMesh(mesh));
    }
  }

  // Nodes
  if (json.contains("nodes")) {
    const auto& nodes = json["nodes"];
    for (const auto& node : nodes) {
      new_gltf.nodes_.push_back(ImportNode(node));
    }
  }

  // Samplers

  // Scene
  if (json.contains("scene")) {
    new_gltf.scene_ = json["scene"];
  }

  // Scenes
  if (json.contains("scenes")) {
    const auto& scenes = json["scenes"];
    for (const auto& scene : scenes) {
      new_gltf.scenes_.push_back(ImportScene(scene));
    }
  }

  // Skins

  // Textures

  // Extensions

  // Extras

  return new_gltf;
}

gltf::Accessor ImportAccessor(const nlohmann::basic_json<>& accessor) {
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

  return new_accessor;
}

gltf::Buffer ImportBuffer(const nlohmann::basic_json<>& buffer) {
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

  return new_buffer;
}

gltf::BufferView ImportBufferView(const nlohmann::basic_json<>& buffer_view) {
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

  return new_buffer_view;
}

gltf::Mesh ImportMesh(const nlohmann::basic_json<>& mesh) {
  gltf::Mesh new_mesh;

  // Primitives - REQUIRED
  if (mesh.contains("primitives")) {
    for (const auto& primitive : mesh["primitives"]) {
      gltf::MeshPrimitive new_mesh_primitive;

      // Attributes - REQUIRED
      if (primitive.contains("attributes")) {
        for (const auto& attribute : primitive["attributes"].items()) {
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

  return new_mesh;
}

gltf::Node ImportNode(const nlohmann::basic_json<>& node) {
  gltf::Node new_node;

  // Camera

  // Children
  if (node.contains("children")) {
    for (const auto& child : node["children"]) {
      new_node.children_.push_back(child);
    }
  }

  // Skin

  // Matrix - DEFAULT : [1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1]
  if (node.contains("matrix")) {
    new_node.matrix_ = node["matrix"];
  }

  // Mesh
  if (node.contains("mesh")) {
    new_node.mesh_ = node["mesh"];
  }

  // Rotation - DEFAULT : [0,0,0,1]
  if (node.contains("rotation")) {
    new_node.rotation_ = node["rotation"];
  }

  // Scale - DEFAULT : [1,1,1]
  if (node.contains("scale")) {
    new_node.scale_ = node["scale"];
  }

  // Translation - DEFAULT : [0,0,0]
  if (node.contains("translation")) {
    new_node.translation_ = node["translation"];
  }

  // Weights

  // Name
  if (node.contains("name")) {
    new_node.name_ = node["name"];
  }

  // Extensions

  // Extras

  return new_node;
}

gltf::Scene ImportScene(const nlohmann::basic_json<>& scene) {
  gltf::Scene new_scene;

  // Nodes
  if (scene.contains("nodes")) {
    for (const auto& node : scene["nodes"]) {
      new_scene.nodes_.push_back(node);
    }
  }

  // Name
  if (scene.contains("name")) {
    new_scene.name_ = scene["name"];
  }

  // Extensions

  // Extras

  return new_scene;
}
}
