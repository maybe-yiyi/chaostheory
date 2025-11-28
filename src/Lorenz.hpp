#pragma once
#include <functional>
#include <glm/vec3.hpp>

class Particle {
  glm::vec3 position;

 public:
  Particle(const glm::vec3& pos) : position(pos) {}

  const glm::vec3& getPosition() const { return position; }

  void update(const std::function<glm::vec3(const glm::vec3&, float)>& dynamics,
              float dt) {
    position = dynamics(position, dt);
  }
};

class LorenzAttractor {
  std::vector<Particle> particles;

 public:
  LorenzAttractor(int numParticles) {
    particles.reserve(numParticles);
    for (int i = 0; i < numParticles; ++i) {
      particles.emplace_back(glm::vec3{
          static_cast<float>(i) / static_cast<float>(numParticles) * 10.0f -
              5.0f,
          1.0f,
          static_cast<float>(i) / static_cast<float>(numParticles) * 10.0f -
              5.0f});
    }
  }

  glm::vec3 operator()(const glm::vec3& pos, float dt) const {
    const float sigma = 10.0f;
    const float rho = 28.0f;
    const float beta = 8.0f / 3.0f;

    glm::vec3 dpos;
    dpos.x = sigma * (pos.y - pos.x);
    dpos.y = pos.x * (rho - pos.z) - pos.y;
    dpos.z = pos.x * pos.y - beta * pos.z;

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