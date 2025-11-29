#pragma once
#include "Particle.hpp"

class RosslerAttractor {
  std::vector<Particle> particles;

 public:
  RosslerAttractor(int numParticles) {
    particles.reserve(numParticles);
    for (int i = 0; i < numParticles; ++i) {
      particles.emplace_back(glm::vec3{
          static_cast<float>(i) / static_cast<float>(numParticles) * 20.0f -
              10.0f,
          static_cast<float>(i) / static_cast<float>(numParticles) * 20.0f -
              10.0f,
          1.0f});
    }
  }

  glm::vec3 operator()(const glm::vec3& pos, float dt) const {
    const float a = 0.2f;
    const float b = 0.2f;
    const float c = 5.7f;

    glm::vec3 dpos;
    dpos.x = -pos.y - pos.z;
    dpos.y = pos.x + a * pos.y;
    dpos.z = b + pos.z * (pos.x - c);

    return pos + dpos * dt;
  }

  void updateParticles(float dt) {
    for (auto& particle : particles) {
      particle.update(
          [this](const glm::vec3& pos, float deltaTime) {
            return (*this)(pos, deltaTime);
          },
          dt);
    }
  }

  const std::vector<Particle>& getParticles() const { return particles; }
};