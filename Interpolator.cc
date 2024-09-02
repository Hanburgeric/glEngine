#include "interpolator.h"

#include "gltf.h"
#include "utils.h"

Interpolator::Interpolator() : prev_key_(0U), prev_time_(0.0F) {}

std::vector<float> Interpolator::Interpolate(const GLTF& gltf,
                                             const AnimationChannel& channel,
                                             const AnimationSampler& sampler,
                                             float t, const std::size_t& stride, float max_time) {
  const Accessor& input_accessor = gltf.accessors_[static_cast<std::size_t>(sampler.input_)];
  const BufferView& input_buffer_view = gltf.buffer_views_[static_cast<std::size_t>(input_accessor.buffer_view_)];
  const Buffer& input_buffer = gltf.buffers_[static_cast<std::size_t>(input_buffer_view.buffer_)];

  const Accessor& output_accessor = gltf.accessors_[static_cast<std::size_t>(sampler.output_)];
  const BufferView& output_buffer_view = gltf.buffer_views_[static_cast<std::size_t>(output_accessor.buffer_view_)];
  const Buffer& output_buffer = gltf.buffers_[static_cast<std::size_t>(output_buffer_view.buffer_)];

  std::int32_t input_byte_offset = input_buffer_view.byte_offset_ + input_accessor.byte_offset_;
  auto input = reinterpret_cast<const float*>(&input_buffer.data_[static_cast<std::size_t>(input_byte_offset)]);
  auto input_length = static_cast<std::size_t>(input_accessor.count_ * GetNumComponentsInType(input_accessor));

  std::int32_t output_byte_offset = output_buffer_view.byte_offset_ + output_accessor.byte_offset_;
  auto output = reinterpret_cast<const float*>(&output_buffer.data_[static_cast<std::size_t>(output_byte_offset)]);

  //Wraps t around so that the animation loops
  //Also ensures that t is never earlier than the first keyframe and never later than the last keyframe
  t = std::fmod(t, max_time);
  t = clamp(t, input[0U], input[input_length - 1U]);
  if (prev_time_ > t) {
    prev_key_ = 0U;
  }
  prev_time_ = t;

  //Finds the next keyframe
  std::size_t next_key;
  for (std::size_t i = prev_key_; i < input_length; i++) {
    if (t <= input[i]) {
      next_key = clamp(i, static_cast<std::size_t>(1U), input_length - 1U);
      break;
    }
  }
  prev_key_ = clamp(next_key - 1U, static_cast<std::size_t>(0U), next_key);
  const float key_delta = input[next_key] - input[prev_key_];

  //Normalizes t
  const float tn = (t - input[prev_key_]) / key_delta;

  //Interpolates the property
  std::vector<float> result;
  if (channel.target_.path_ == "rotation") {
    //Rotation
    glm::quat quat(NAN, NAN, NAN, NAN);
    if (sampler.interpolation_ == "CUBICSPLINE") {
      //Cubic spline
      result = CubicSpline(next_key, output, key_delta, tn, 4U);
      quat = glm::normalize(glm::quat(result[3U], result[0U], result[1U], result[2U]));
      result.clear();
    } else if (sampler.interpolation_ == "STEP") {
      //Step
      quat = Interpolator::GetQuat(output, prev_key_);
    } else {
      //Linear
      const glm::quat q0 = Interpolator::GetQuat(output, prev_key_);
      const glm::quat q1 = Interpolator::GetQuat(output, next_key);
      quat = glm::slerp(q0, q1, tn);
    }
    for (std::int32_t i = 0; i < 4; i++) {
      result.push_back(quat[i]);
    }
  } else {
    //Translation, scale, weight
    if (sampler.interpolation_ == "CUBICSPLINE") {
      //Cubic spline
      result = CubicSpline(next_key, output, key_delta, tn, stride);
    } else if (sampler.interpolation_ == "STEP") {
      //Step
      result = Step(output, stride);
    } else {
      //Linear
      result = Linear(next_key, output, tn, stride);
    }
  }
  return result;
}

std::vector<float> Interpolator::Step(const float* output, const std::size_t& stride) const {
  std::vector<float> result;
  for (std::size_t i = 0U; i < stride; i++) {
    result.push_back(output[prev_key_ * stride + i]);
  }
  return result;
}

std::vector<float> Interpolator::Linear(const std::size_t& next_key, const float* output,
                                        const float& t, const std::size_t& stride) const {
  std::vector<float> result;
  for (std::size_t i = 0U; i < stride; i++) {
    result.push_back(output[prev_key_ * stride + i] * (1.0F - t) + output[next_key * stride + i] * t);
  }
  return result;
}

std::vector<float> Interpolator::CubicSpline(const std::size_t& next_key, const float* output,
                                             const float& key_delta, const float& t, const std::size_t& stride) const {
  std::vector<float> result;
  const std::size_t prev_index = prev_key_ * stride * 3U;
  const std::size_t next_index = next_key * stride * 3U;
  const float t_sq = t * t;
  const float t_cub = t_sq * t;
  for (std::size_t i = 0U; i < stride; i++) {
    const float v0 = output[prev_index + i + stride];
    const float a = key_delta * output[next_index + i];
    const float b = key_delta * output[prev_index + i + (2U * stride)];
    const float v1 = output[next_index + i + stride];
    result.push_back(((2.0F * t_cub - 3.0F * t_sq + 1.0F) * v0) + ((t_cub - 2.0F * t_sq + t) * b) +
        ((-2.0F * t_cub + 3.0F * t_sq) * v1) + ((t_cub - t_sq) * a));
  }
  return result;
}

glm::quat Interpolator::GetQuat(const float* output, const std::size_t& index) {
  const std::size_t offset = static_cast<std::size_t>(glm::quat::length()) * index;
  return {output[offset + 3U],
          output[offset],
          output[offset + 1U],
          output[offset + 2U]};
}
