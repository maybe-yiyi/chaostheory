#include <SFML/Graphics.hpp>
#include <functional>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>
#include <iostream>

#include "Lorenz.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Window",
                          sf::State::Fullscreen);
  window.setFramerateLimit(60);

  LorenzAttractor lorenzAttractor(1500);

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
        }
      }
    }

    window.clear(sf::Color::Black);

    std::for_each(lorenzAttractor.getParticles().begin(),
                  lorenzAttractor.getParticles().end(),
                  [&](const Particle& particle) {
                    sf::CircleShape shape(2);
                    shape.setFillColor(sf::Color::White);
                    shape.setPosition({960 + particle.getPosition().x * 10,
                                       540 + particle.getPosition().y * 10});

                    window.draw(shape);
                  });
    window.display();
  }

  return 0;
}