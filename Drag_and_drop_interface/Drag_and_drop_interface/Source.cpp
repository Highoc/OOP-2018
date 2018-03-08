#include <cstdlib>
#include <iostream>
#include "Container.hpp"


sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1024, 800), "Drag'n'Drop Interface");
sf::Font font;

int main()
{
	font.loadFromFile("font.ttf");

	Container containerOne(20, 20,  4, 6, 60, 1);
	Container containerTwo(20, 400, 3, 6, 60, 1);

	containerOne.getFrame(1, 2).setValue("X");
	containerOne.getFrame(1, 0).setValue("Y");
	containerOne.getFrame(0, 0).setValue("I");
	containerTwo.getFrame(0, 1).setValue("R");
	containerTwo.getFrame(0, 2).setValue("O");
	containerTwo.getFrame(0, 3).setValue("M");
	containerTwo.getFrame(0, 4).setValue("A");
	containerTwo.getFrame(0, 5).setValue("P");
	containerTwo.getFrame(1, 0).setValue("I");
	containerTwo.getFrame(1, 1).setValue("D");
	containerTwo.getFrame(1, 2).setValue("O");
	containerTwo.getFrame(1, 3).setValue("R");
	containerTwo.getFrame(1, 4).setValue("!");

	while (window->isOpen())
	{
		sf::Event event;
		if (window->pollEvent(event))
		{
			window->clear();	

			containerOne.draw();
			containerTwo.draw();
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
			{
				size_t x = event.mouseButton.x;
				size_t y = event.mouseButton.y;

				containerOne.handler_pressedButton(x, y);
				containerTwo.handler_pressedButton(x, y);
			}
				break;

			case sf::Event::MouseButtonReleased:
			{
				size_t x = event.mouseButton.x;
				size_t y = event.mouseButton.y;

				int resultOne = containerOne.handler_releasedButton(x, y);
				int resultTwo = containerTwo.handler_releasedButton(x, y);

				if ((resultOne == 0) && (resultTwo == 0))
				{
					Container::trader.cancelTrade();
				}
			}
				break;

			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::MouseMoved:
				if (Container::trader.getState())
				{
					Container::trader.updateAnimation(event.mouseMove.x, event.mouseMove.y);
				}
				break;
			}
			
		}

		window->display();
	}

	system("pause");
	return 0;
}