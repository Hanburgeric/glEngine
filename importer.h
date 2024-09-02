#ifndef GRAPICAR__IMPORTER_H_
#define GRAPICAR__IMPORTER_H_

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include <document.h>

#include "gltf.h"

class Importer {
 public:
  void LoadASCIIFromFile(GLTF& gltf, const std::string& path);

 private:
  void LoadDocument(const std::string& path);

  void LoadAccessors(GLTF& gltf);
  void LoadAnimations(GLTF& gltf);
  void LoadBuffers(GLTF& gltf, const std::string& path);
  void LoadBufferViews(GLTF& gltf);
//  void LoadCameras(GLTF& gltf);
//  void LoadImages(GLTF& gltf);
//  void LoadMaterials(GLTF& gltf);
  void LoadMeshes(GLTF& gltf);
  void LoadNodes(GLTF& gltf);
//  void LoadSamplers(GLTF& gltf);
  void LoadScene(GLTF& gltf);
  void LoadScenes(GLTF& gltf);
//  void LoadSkins(GLTF& gltf);
//  void LoadTextures(GLTF& gltf);

  template <typename T, std::size_t L, typename U>
  void CopyGenericArrayToArray(std::array<T, L>& dst, const rapidjson::GenericArray<true, U>& src) {
    for (rapidjson::SizeType i = 0U; i < src.Size(); i++) {
      dst[i] = static_cast<const rapidjson::Value&>(src[i]).Get<T>();
    }
  }

  template <typename T, typename U>
  void CopyGenericArrayToVector(std::vector<T>& dst, const rapidjson::GenericArray<true, U>& src) {
    for (rapidjson::SizeType i = 0U; i < src.Size(); i++) {
      dst.push_back(static_cast<const rapidjson::Value&>(src[i]).Get<T>());
    }
  }

  rapidjson::Document document_;
};

#endif //GRAPICAR__IMPORTER_H_
