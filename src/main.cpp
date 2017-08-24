#include <SFML/Graphics.hpp>
#include "AstarAlgo.h"
#include <chrono>
#include <thread>
#include <iostream>

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(1600, 1000), "Pathfind");
	cellGenerator test(8, 1, 100, 100, sf::Vector2f(20, 20), &window, 0);
	BreadthAlgo * algo;
	algo = new Dijkstra(&test);
	algo->Init();

	sf::Font font;
	sf::Text text;
	if (!font.loadFromFile("data/arial.ttf")) {
		return EXIT_FAILURE;
	}

	text.setFont(font);
	text.setString("C : Breadth\nV : Dijkstra\nB : A*\nReturn : Pause / Resume");
	text.setPosition(sf::Vector2f(window.getSize().x - (10 * text.getCharacterSize()),50));
	text.setCharacterSize(25);
	algo->setStop(true);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Return)
					algo->setStop(!algo->getStop());
				if (event.key.code == sf::Keyboard::Up)
					test.moveCursor(sf::Vector2f(0, -1));
				if (event.key.code == sf::Keyboard::Down)
					test.moveCursor(sf::Vector2f(0, 1));
				if (event.key.code == sf::Keyboard::Right)
					test.moveCursor(sf::Vector2f(1, 0));
				if (event.key.code == sf::Keyboard::Left)
					test.moveCursor(sf::Vector2f(-1, 0));
				if (event.key.code == sf::Keyboard::P && algo->getStop())
					test.getCursor()->changeSide();
				if (event.key.code == sf::Keyboard::C) {
					algo->reset();
					delete algo;
					algo = new BreadthAlgo(&test);
					algo->Init();
					algo->setStop(true);
				}
				if (event.key.code == sf::Keyboard::V) {
					algo->reset();
					delete algo;
					algo = new Dijkstra(&test);
					algo->Init();
					algo->setStop(true);
				}
				if (event.key.code == sf::Keyboard::B) {
					algo->reset();
					delete algo;
					algo = new Astar(&test);
					algo->Init();
					algo->setStop(true);
				}
			}
		}
		if (!algo->getStop()) {
			//std::this_thread::sleep_for(std::chrono::milliseconds(25));
			algo->next();
		}
		window.clear();
		test.draw();
		window.draw(text);
		window.display();
	}
	return 0;
}