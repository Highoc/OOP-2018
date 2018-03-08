#pragma once

#include "Frame.hpp"

class ManagerTrade
{
public:
	ManagerTrade();
	~ManagerTrade();

	void addSender(Frame *sender);
	void addReceiver(Frame *reciever);
	void doTrade();
	void cancelTrade();

	bool getState();

	void updateAnimation(size_t x, size_t y);

	size_t oldX_;
	size_t oldY_;

private:	
	Frame* sender_;
	Frame* receiver_;
	Frame* animationFrame_;
	bool tradeState_;
};