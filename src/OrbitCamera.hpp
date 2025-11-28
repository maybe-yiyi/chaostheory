#pragma once
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class OrbitCamera {
  glm::vec3 center;
  glm::vec3 upVector;
  float minRadius;
  float radius;
  float azimuthAngle;
  float polarAngle;

 public:
  OrbitCamera(const glm::vec3& centerPos, float radius, float azim,
              float polarAngle)
      : center(centerPos),
        radius(radius),
        azimuthAngle(azim),
        polarAngle(polarAngle) {}

  glm::vec3 getPosition() const {
    float x = center.x + radius * cos(polarAngle) * sin(azimuthAngle);
    float y = center.y + radius * sin(polarAngle);
    float z = center.z + radius * cos(polarAngle) * cos(azimuthAngle);
    return glm::vec3{x, y, z};
  }

  void rotateAzimuth(float deltaAzim) {
    azimuthAngle += deltaAzim;
    const auto twoPi = glm::two_pi<float>();
    if (azimuthAngle > twoPi) azimuthAngle -= twoPi;
    if (azimuthAngle < 0.0f) azimuthAngle += twoPi;
  }

  void rotatePolar(float deltaPolar) {
    polarAngle += deltaPolar;
    const auto polarAngleCap = glm::half_pi<float>() - 0.01f;
    if (polarAngle > polarAngleCap) polarAngle = polarAngleCap;
    if (polarAngle < -polarAngleCap) polarAngle = -polarAngleCap;
  }

  void zoom(float deltaDistance) {
    radius += deltaDistance;
    if (radius < minRadius) radius = minRadius;
  }
};