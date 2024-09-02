#ifndef GRAPICAR__INTERPOLATOR_H_
#define GRAPICAR__INTERPOLATOR_H_

#include <vector>

#include <glm/gtx/quaternion.hpp>

struct AnimationChannel;
struct AnimationSampler;
struct GLTF;

class Interpolator {
 public:
  Interpolator();

  std::vector<float> Interpolate(const GLTF& gltf,
                                 const AnimationChannel& channel,
                                 const AnimationSampler& sampler,
                                 float t, const std::size_t& stride, float max_time);

 private:
  std::vector<float> Step(const float* output, const std::size_t& stride) const;
  std::vector<float> Linear(const std::size_t& next_key, const float* output,
                            const float& t, const std::size_t& stride) const;
  std::vector<float> CubicSpline(const std::size_t& next_key, const float* output,
                                 const float& key_delta, const float& t, const std::size_t& stride) const;

  static glm::quat GetQuat(const float* output, const std::size_t& index);

  std::size_t prev_key_;
  float prev_time_;
};

#endif //GRAPICAR__INTERPOLATOR_H_
