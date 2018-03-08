#include "ManagerTrade.hpp"

ManagerTrade::ManagerTrade() :
	oldX_(0), oldY_(0),
	sender_(nullptr),
	receiver_(nullptr),
	animationFrame_(nullptr),
	tradeState_(false)
{}

ManagerTrade::~ManagerTrade()
{}

void ManagerTrade::addSender(Frame *sender)
{
	if (tradeState_)
	{
		return;
	}

	sender_ = sender;
	tradeState_ = true;
	sender->setState(BLOCKED);

	animationFrame_ = new Frame(*sender_);
}

void ManagerTrade::addReceiver(Frame *receiver)
{
	if (!tradeState_)
	{
		return;
	}

	receiver_ = receiver;
	receiver_->setState(BLOCKED);
	doTrade();
}

void ManagerTrade::doTrade()
{
	sender_->setState(EMPTY);
	receiver_->setState(EMPTY);

	std::string swap = sender_->getValue();
	sender_->setValue(receiver_->getValue());
	receiver_->setValue(swap);

	tradeState_ = false;
	delete animationFrame_;
}

bool ManagerTrade::getState()
{
	return tradeState_;
}

void ManagerTrade::updateAnimation(size_t x, size_t y)
{
	animationFrame_->move(x - oldX_, y - oldY_);
	animationFrame_->setState(FrameState::MOVED);
	
	animationFrame_->draw();

	oldX_ = x;
	oldY_ = y;
}

void ManagerTrade::cancelTrade()
{
	sender_->setState(EMPTY);
	receiver_->setState(EMPTY);
	
	tradeState_ = false;

	animationFrame_ = NULL;
	delete animationFrame_;
}