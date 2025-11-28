#include <iostream>

#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Window", sf::State::Fullscreen);

  while (window.isOpen()) {
    while(const std::optional event = window.pollEvent()) {
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

    window.display();
  }

  return 0;
}