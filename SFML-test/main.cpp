#include <iostream>
#include <SFML/Graphics.hpp>

#include "ParticleSystem.h"
//#include "RoundedRectangleShape.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML-test", sf::Style::Close | sf::Style::Titlebar);
	   
	sf::Event event;

	sf::RectangleShape target;
	target.setSize(sf::Vector2f(4.f, 4.f));
	target.setPosition(640.f, 360.f);
	target.setOrigin(2.f, 2.f);
	target.setFillColor(sf::Color::Cyan);

	ParticleSystem particles(1000, target.getGlobalBounds(), 4.f);

	sf::Clock clock;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
				break;
			}
		}

		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		particles.setEmitter(window.mapPixelToCoords(mouse));

		sf::Time elapsed = clock.restart();
		particles.update(elapsed);

		window.clear();
		window.draw(particles);
		window.display();
	}
	return 0;
}