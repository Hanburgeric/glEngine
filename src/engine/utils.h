#ifndef GLENGINE_SRC_ENGINE_UTILS_H_
#define GLENGINE_SRC_ENGINE_UTILS_H_

// System headers
#include <string>

namespace glEngine::utils {
bool IsUriEmbedded(const std::string& uri);
int ComponentTypeToByteSize(int component_type);
int TypeToNumComponents(const std::string& type);
}

#endif //GLENGINE_SRC_ENGINE_UTILS_H_
