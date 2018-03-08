#include "Frame.hpp"

Frame::Frame():
	Frame(nullptr, 0, 0, 0)
{}

Frame::Frame(Container* parent, size_t x, size_t y, size_t frameSize):
	x_(x), y_(y),
	frameSize_(frameSize),
	parent_(parent),
	rectangle_(sf::RectangleShape(sf::Vector2f(frameSize, frameSize))),
	color_(sf::Color::White),
	state_(FrameState::EMPTY),
	value_("")
{}

Frame::~Frame()
{}

void Frame::draw()
{
	rectangle_.setPosition(x_, y_);
	rectangle_.setFillColor(color_);
	window->draw(rectangle_);
	
	if(state_ != BLOCKED)
	{
		sf::Text text;
		text.setPosition(x_ + frameSize_ / 5, y_ + frameSize_ / 5);
		text.setFont(font);
		text.setString(value_);
		text.setCharacterSize(frameSize_ / 2);
		text.setFillColor(sf::Color::Blue);
		
		window->draw(text);
	}
}

int Frame::handler_pressedButton(size_t x, size_t y)
{
	return rectangle_.getGlobalBounds().contains(x, y);
}

int Frame::handler_releasedButton(size_t x, size_t y)
{
	return rectangle_.getGlobalBounds().contains(x, y);
}

sf::RectangleShape& Frame::getRectangle()
{
	return rectangle_;
}

FrameState Frame::getState()
{
	return state_;
}

void Frame::setValue(std::string value)
{
	value_ = value;
}

std::string Frame::getValue()
{
	return value_;
}

void Frame::move(size_t x, size_t y)
{
	x_ += x;
	y_ += y;
}

void Frame::setState(FrameState state)
{
	state_ = state;

	switch (state_)
	{
	case FrameState::EMPTY:
		color_ = sf::Color::White;
		break;
	case FrameState::BLOCKED:
		color_ = sf::Color::White;
		break;
	case FrameState::MOVED:
		color_ = sf::Color::Transparent;
		break;
	}
}