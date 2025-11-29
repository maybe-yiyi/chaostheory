#include <functional>
#include <glm/glm.hpp>

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