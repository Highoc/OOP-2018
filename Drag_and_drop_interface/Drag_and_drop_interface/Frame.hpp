#pragma once

#include "SFML\Graphics.hpp"
#include <string>

extern class Container;
extern sf::RenderWindow* window;
extern sf::Font font;

enum FrameState
{
	EMPTY,
	FILL,
	BLOCKED,
	FORBIDDEN,
	MOVED
};

class Frame
{
public:
	Frame();
	Frame(Container* parent, size_t x, size_t y, size_t frameSize_);
	~Frame();

	sf::RectangleShape& getRectangle();
	FrameState getState();
	void setState(FrameState state);

	void setValue(std::string value);
	std::string getValue();

	void move(size_t x, size_t y);

	int handler_pressedButton(size_t x, size_t y);
	int handler_releasedButton(size_t x, size_t y);

	void draw();

private:
	size_t x_, y_;
	size_t frameSize_;

	Container* parent_;

	sf::RectangleShape rectangle_;
	sf::Color color_;
	
	FrameState state_;

	std::string value_;
};