#include "Interpolator.h"

#include <cstdio>

#include "utils.h"

template<typename T>
T clamp(const T& t, const T& min, const T& max) {
  const T a = t < min ? min : t;
  return a > max ? max : a;
}

Interpolator::Interpolator() : prevKey(0U), prevT(0.0F) {}

glm::vec4 Interpolator::step(const float* output, const std::size_t& stride) const {
  glm::vec4 result(NAN, NAN, NAN, NAN);
  for (std::size_t i = 0U; i < stride; i++) {
    result[static_cast<int>(i)] = output[this->prevKey * stride + i];
  }
  return result;
}

glm::vec4 Interpolator::linear(const std::size_t& nextKey, const float* output, const float& t, const std::size_t& stride) const {
  glm::vec4 result(NAN, NAN, NAN, NAN);
  for (std::size_t i = 0U; i < stride; i++) {
    result[static_cast<int>(i)] = output[this->prevKey * stride + i] * (1.0F - t) + output[nextKey * stride + i] * t;
  }
  return result;
}

glm::vec4 Interpolator::cubicSpline(const std::size_t& nextKey, const float* output, const float& keyDelta, const float& t, const std::size_t& stride) const {
  glm::vec4 result(NAN, NAN, NAN, NAN);

  const std::size_t prevIndex = this->prevKey * stride * 3U;
  const std::size_t nextIndex = nextKey * stride * 3U;
  const float tSq = t * t;
  const float tCub = tSq * t;

  for (std::size_t i = 0U; i < stride; i++) {
    const float v0 = output[prevIndex + i + stride];
    const float a = keyDelta * output[nextIndex + i];
    const float b = keyDelta * output[prevIndex + i + (2U * stride)];
    const float v1 = output[nextIndex + i + stride];

    result[static_cast<int>(i)] = ((2.0F * tCub - 3.0F * tSq + 1.0F) * v0) + ((tCub - 2.0F * tSq + t) * b) + ((-2.0F * tCub + 3.0F * tSq) * v1) + ((tCub - tSq) * a);
  }

  return result;
}

void Interpolator::resetKey() { this->prevKey = 0U; }

glm::vec4 Interpolator::interpolate(const GLTF& gltf,
                                    const AnimationChannel& channel,
                                    const AnimationSampler& sampler,
                                    float t,
                                    const std::size_t& stride,
                                    float maxTime) {
  //Provides a view to the accessors' data in the form of an array.
  const Accessor& inputAccessor = gltf.accessors_[sampler.input_];
  const BufferView& inputBufferView = gltf.buffer_views_[inputAccessor.buffer_view_];
  const Buffer& inputBuffer = gltf.buffers_[inputBufferView.buffer_];

  const Accessor& outputAccessor = gltf.accessors_[sampler.output_];
  const BufferView& outputBufferView = gltf.buffer_views_[outputAccessor.buffer_view_];
  const Buffer& outputBuffer = gltf.buffers_[outputBufferView.buffer_];

  auto input = reinterpret_cast<const float*>(&inputBuffer.data_[inputBufferView.byte_offset_ + inputAccessor.byte_offset_]);
  const std::size_t inputLength = static_cast<std::size_t>(inputAccessor.count_ * GetNumComponentsInType(inputAccessor));

  auto output = reinterpret_cast<const float*>(&outputBuffer.data_[outputBufferView.byte_offset_ + outputAccessor.byte_offset_]);

  //Wraps t around so that the animation loops; also ensures that t is never earlier than the first keyframe and never later than the last keyframe
  t = std::fmod(t, maxTime);
  t = clamp(t, input[0], input[inputLength - 1U]);
  if (this->prevT > t) {
    this->prevKey = 0U;
  }
  this->prevT = t;

  //Finds the next keyframe
  std::size_t nextKey;
  for (std::size_t i = this->prevKey; i < inputLength; i++) {
    if (t <= input[i]) {
      nextKey = clamp(i, static_cast<std::size_t>(1U), inputLength - 1U);
      break;
    }
  }
  this->prevKey = clamp(nextKey - 1U, static_cast<std::size_t>(0U), nextKey);
  const float keyDelta = input[nextKey] - input[this->prevKey];

  //Normalizes t
  const float tn = (t - input[this->prevKey]) / keyDelta;

  //Interpolates the property
  glm::vec4 result(NAN, NAN, NAN, NAN);
  if (channel.target_.path_[0U] == 'r') {
    //Rotation
    glm::quat resQuat(NAN, NAN, NAN, NAN);
    if (sampler.interpolation_[0U] == 'C') {
      //Cubic spline
      result = this->cubicSpline(nextKey, output, keyDelta, tn, static_cast<std::size_t>(glm::quat::length()));
      resQuat = glm::normalize(glm::quat(result.w, result.x, result.y, result.z));
    } else if (sampler.interpolation_[0U] == 'S') {
      //Step
      resQuat = Interpolator::getQuat(output, this->prevKey);
    } else {
      //Linear
      const glm::quat q0 = Interpolator::getQuat(output, this->prevKey);
      const glm::quat q1 = Interpolator::getQuat(output, nextKey);
      resQuat = glm::slerp(q0, q1, tn);
    }
    result = glm::vec4(resQuat.x, resQuat.y, resQuat.z, resQuat.w);
  } else {
    //Translation, scale, weight
    if (sampler.interpolation_[0U] == 'C') {
      //Cubic spline
      result = this->cubicSpline(nextKey, output, keyDelta, tn, stride);
    } else if (sampler.interpolation_[0U] == 'S') {
      //Step
      result = this->step(output, stride);
    } else {
      //Linear
      result = this->linear(nextKey, output, tn, stride);
    }
  }
  return result;
}

glm::quat Interpolator::getQuat(const float* output, const std::size_t& index) {
  const std::size_t offset = static_cast<std::size_t>(glm::quat::length()) * index;
  return {output[offset + 3U],
          output[offset],
          output[offset + 1U],
          output[offset + 2U]};
}
