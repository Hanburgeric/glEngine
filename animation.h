#ifndef GRAPICAR__ANIMATION_H_
#define GRAPICAR__ANIMATION_H_

#include <cstdint>
#include <string>
#include <vector>

#include "interpolator.h"

struct AnimationChannelTarget {
  std::int32_t node_;
  std::string path_;
};

struct AnimationChannel {
  std::int32_t sampler_;
  AnimationChannelTarget target_;
};

struct AnimationSampler {
  std::int32_t input_;
  std::string interpolation_;
  std::int32_t output_;
};

struct Animation {
  std::vector<AnimationChannel> channels_;
  std::vector<AnimationSampler> samplers_;
  std::string name_;

  std::vector<Interpolator> interpolators_;
  float max_time_; //Number assumed to be a float
};

#endif //GRAPICAR__ANIMATION_H_
