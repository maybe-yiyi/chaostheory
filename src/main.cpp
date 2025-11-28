#include <SFML/Graphics.hpp>
#include <functional>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>
#include <iostream>

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

int main() {
  sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Window",
                          sf::State::Fullscreen);

  std::vector<Particle> particles;
  particles.reserve(1000);

  for (size_t i = 0; i < 1000; i++) {
    particles.emplace_back(glm::vec3{static_cast<float>(i / 100.f) - 5.0f, 1.0f,
                                     static_cast<float>(i / 100.f) - 5.0f});
  }

  auto lorenzattractor = [&](const glm::vec3& pos, const float dt) {
    const float sigma = 10.0f;
    const float rho = 28.0f;
    const float beta = 8.0f / 3.0f;

    glm::vec3 dpos;
    dpos.x = sigma * (pos.y - pos.x);
    dpos.y = pos.x * (rho - pos.z) - pos.y;
    dpos.z = pos.x * pos.y - beta * pos.z;

    return pos + dpos * dt;
  };

  sf::Clock clock;
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();
    std::for_each(particles.begin(), particles.end(), [&](Particle& particle) {
      particle.update(lorenzattractor, dt);
    });

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (event->is<sf::Event::KeyPressed>()) {
        const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
        if (keyEvent->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }
    }

    window.clear(sf::Color::Black);

    std::for_each(particles.begin(), particles.end(),
                  [&](const Particle& particle) {
                    sf::CircleShape shape(5);
                    shape.setFillColor(sf::Color::White);
                    shape.setPosition({960 + particle.getPosition().x * 10,
                                       540 + particle.getPosition().y * 10});

                    window.draw(shape);
                  });
    window.display();
  }

  return 0;
}