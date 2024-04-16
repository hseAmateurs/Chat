//
// Created by Shon on 12.04.2024.
// Hello from client and Sonya
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    std::cout << "Hello from client6\n";

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
