#include "Container.hpp"

ManagerTrade Container::trader = ManagerTrade();

Container::Container(	size_t x, size_t y, size_t frameLineN, size_t frameColumnN, size_t frameSize, size_t zIndex,
						size_t borderWidth, size_t borderPadding, size_t marginFrame) :
	x_(x), y_(y),
	width_(0), length_(0),
	zIndex_(zIndex),
	containerRect_(),
	frameLineN_(frameLineN), frameColumnN_(frameColumnN),
	frames_(),
	borderWidth_(borderWidth), borderPadding_(borderPadding),
	marginFrame_(marginFrame)
{
	length_ = 2 * borderPadding_ + 2 * borderWidth_ + frameColumnN_ * frameSize + (frameColumnN_ + 1) * marginFrame_;
	width_  = 2 * borderPadding_ + 2 * borderWidth_ + frameLineN_ * frameSize + (frameLineN_ + 1) * marginFrame_;
	
	containerRect_ = sf::RectangleShape(sf::Vector2f(length_, width_));

	frames_ = std::vector<std::vector<Frame>>(frameLineN_);
	for (size_t i = 0; i < frameLineN_; i++)
	{
		frames_[i] = std::vector<Frame>(frameColumnN_);
		for (size_t j = 0; j < frameColumnN_; j++)
		{
			frames_[i][j] = Frame(this,
				x_ + borderWidth_ + borderPadding_ + marginFrame_ + (marginFrame_ + frameSize)*j,
				y_ + borderWidth_ + borderPadding_ + marginFrame_ + (marginFrame_ + frameSize)*i,
				frameSize);
		}
	}
}

Container::~Container()
{

}

void Container::draw()
{
	containerRect_.setPosition(x_, y_);
	containerRect_.setFillColor(sf::Color::Red);
	window->draw(containerRect_);

	for (auto& nowLine : frames_)
	{
		for (auto& nowFrame : nowLine)
		{
			nowFrame.draw();
		}
	}
}

const sf::RectangleShape& Container::getRect()
{
	return containerRect_;
}

int Container::handler_pressedButton(size_t x, size_t y)
{
	if (!getRect().getGlobalBounds().contains(x, y))
	{
		return 0;
	}

	std::cout << "> handler_pressedButton()  in Container( " << this << " )";
	
	for (size_t i = 0; i < frameLineN_; i++)
	{
		for (size_t j = 0; j < frameColumnN_; j++)
		{
			if (frames_[i][j].handler_pressedButton(x, y))
			{
				std::cout << " in Frame[" << i << "][" << j << "]( " << &(frames_[i][j]) << " )" << std::endl;

				trader.oldX_ = x;
				trader.oldY_ = y;
				trader.addSender(&(frames_[i][j]));
				return 1;
			}
		}
	}

	std::cout << ", but isn't in Frame" << std::endl;
	return 0;
}

int Container::handler_releasedButton(size_t x, size_t y)
{
	if (!getRect().getGlobalBounds().contains(x, y))
	{
		return 0;
	}

	std::cout << "> handler_releasedButton() in Container( " << this << " )";

	for (size_t i = 0; i < frameLineN_; i++)
	{
		for (size_t j = 0; j < frameColumnN_; j++)
		{
			if (frames_[i][j].handler_releasedButton(x, y))
			{
				std::cout << " in Frame[" << i << "][" << j << "]( " << &(frames_[i][j]) << " )" << std::endl;

				trader.addReceiver(&(frames_[i][j]));
				return 1;
			}
		}
	}

	trader.cancelTrade();
	std::cout << ", but isn't in Frame" << std::endl;
	return 0;
}


Frame& Container::getFrame(size_t i, size_t j)
{
	return frames_[i][j];
}