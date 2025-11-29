#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "Lorenz.hpp"
#include "OrbitCamera.hpp"

int main() {
  const glm::uvec2 windowSize{1920, 1080};
  const glm::vec2 viewportSize{1920.f, 1080.f};

  sf::RenderWindow window(sf::VideoMode({windowSize.x, windowSize.y}), "Window",
                          sf::State::Fullscreen);
  window.setFramerateLimit(60);
  sf::View view({0, 0}, {viewportSize.x, viewportSize.y});
  window.setView(view);

  LorenzAttractor lorenzAttractor(1500);
  OrbitCamera camera(glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                     1.0f, 30.0f);

  sf::Clock clock;
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();
    lorenzAttractor.updateParticles(dt);

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (event->is<sf::Event::KeyPressed>()) {
        const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
        if (keyEvent->code == sf::Keyboard::Key::Escape) {
          window.close();
        } else if (keyEvent->code == sf::Keyboard::Key::Up) {
          camera.zoom(-0.1f);
        } else if (keyEvent->code == sf::Keyboard::Key::Down) {
          camera.zoom(0.1f);
        } else if (keyEvent->code == sf::Keyboard::Key::A) {
          camera.orbitYaw(-0.1f);
        } else if (keyEvent->code == sf::Keyboard::Key::D) {
          camera.orbitYaw(0.1f);
        } else if (keyEvent->code == sf::Keyboard::Key::W) {
          camera.orbitPitch(0.1f);
        } else if (keyEvent->code == sf::Keyboard::Key::S) {
          camera.orbitPitch(-0.1f);
        }
      }
    }

    window.clear(sf::Color::Black);

    glm::mat4x4 viewMatrix = camera.getViewMatrix();
    std::for_each(lorenzAttractor.getParticles().begin(),
                  lorenzAttractor.getParticles().end(),
                  [&](const Particle& particle) {
                    sf::CircleShape shape(2);

                    glm::vec3 pos = particle.getPosition();
                    glm::vec4 homogenousPos{pos.x, pos.y, pos.z, 1.0f};
                    glm::vec4 viewPos = viewMatrix * homogenousPos;
                    float ndcX = viewPos.x / -viewPos.z;
                    float ndcY = viewPos.y / -viewPos.z;
                    float screenX = ndcX * 0.5f * viewportSize.x;
                    float screenY = -ndcY * 0.5f * viewportSize.y;
                    shape.setPosition({screenX, screenY});
                    shape.setFillColor(sf::Color::White);

                    window.draw(shape);
                  });
    window.display();
  }

  return 0;
}