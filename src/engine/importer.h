#ifndef GLENGINE_SRC_ENGINE_IMPORTER_H_
#define GLENGINE_SRC_ENGINE_IMPORTER_H_

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
gltf::Gltf ImportGltfFromJson(const nlohmann::json& json);

gltf::Accessor ImportAccessor(const nlohmann::basic_json<>& accessor);
gltf::Buffer ImportBuffer(const nlohmann::basic_json<>& buffer);
gltf::BufferView ImportBufferView(const nlohmann::basic_json<>& buffer_view);
gltf::Mesh ImportMesh(const nlohmann::basic_json<>& mesh);
gltf::Node ImportNode(const nlohmann::basic_json<>& node);
gltf::Scene ImportScene(const nlohmann::basic_json<>& scene);
}

#endif //GLENGINE_SRC_ENGINE_IMPORTER_H_
