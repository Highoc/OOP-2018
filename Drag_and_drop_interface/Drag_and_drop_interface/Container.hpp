#pragma once

#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

#include "SFML\Graphics.hpp"
#include "Frame.hpp"
#include "ManagerTrade.hpp"

extern sf::RenderWindow* window;

class Container
{
public:
	Container(	size_t x, size_t y,
				size_t frameLineN, size_t frameColumnN,
				size_t frameSize,
				size_t zIndex,
				size_t borderWidth = 4, size_t borderPadding = 0, 
				size_t marginFrame = 4 
	);

	~Container();

	const sf::RectangleShape& getRect();
	Frame& getFrame(size_t i, size_t j);

	int handler_pressedButton (size_t x, size_t y);
	int handler_releasedButton(size_t x, size_t y);

	void draw();
	
	static ManagerTrade trader; //â private

private:
	size_t x_, y_;
	size_t width_, length_;
	size_t zIndex_;

	sf::RectangleShape containerRect_;

	size_t frameLineN_, frameColumnN_;

	std::vector<std::vector<Frame>> frames_;

	size_t borderWidth_, borderPadding_;
	size_t marginFrame_;
};


