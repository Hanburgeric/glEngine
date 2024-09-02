#ifndef INTERPOLATOR_H_
#define INTERPOLATOR_H_

#include <glm/gtx/quaternion.hpp>

#include "gltf.h"

template<typename T>
T clamp(const T& t, const T& min, const T& max);

class Interpolator {
 public:
  Interpolator();

  glm::vec4 step(const float* output, const std::size_t& stride) const;
  glm::vec4 linear(const std::size_t& nextKey, const float* output, const float& t, const std::size_t& stride) const;
  glm::vec4 cubicSpline(const std::size_t& nextKey, const float* output, const float& keyDelta, const float& t, const std::size_t& stride) const;
  void resetKey();
  glm::vec4 interpolate(const GLTF& gltf,
                        const AnimationChannel& channel,
                        const AnimationSampler& sampler,
                        float t,
                        const std::size_t& stride,
                        float maxTime);
  static glm::quat getQuat(const float* output, const std::size_t& index);

 private:
  std::size_t prevKey;
  float prevT;
};

#endif
