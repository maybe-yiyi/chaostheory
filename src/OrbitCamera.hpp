#pragma once
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class OrbitCamera {
  glm::vec3 center;
  glm::vec3 position;  // relative to center
  glm::vec3 upVector;
  float minRadius;

 public:
  OrbitCamera(const glm::vec3& centerPos, const glm::vec3& upVec,
              float minRadius, float radius)
      : center(centerPos),
        upVector(upVec),
        minRadius(minRadius),
        position(glm::vec3(radius, 0.0f, 0.0f)) {}

  void orbitYaw(float angleDelta) {
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angleDelta, upVector);
    position = glm::vec3(rotationMatrix * glm::vec4(position, 1.0f));
  }

  void orbitPitch(float angleDelta) {
    glm::vec3 rightVector = glm::normalize(glm::cross(position, upVector));
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angleDelta, rightVector);
    position = glm::vec3(rotationMatrix * glm::vec4(position, 1.0f));
    upVector = glm::normalize(glm::cross(rightVector, position));
  }

  void zoom(float deltaDistance) {
    float radius = glm::length(position);
    radius += deltaDistance;
    radius = glm::max(radius, minRadius);
    position = glm::normalize(position) * radius;
  }

  glm::mat4x4 getViewMatrix() const {
    return glm::lookAt(position + center, center, upVector);
  }
};