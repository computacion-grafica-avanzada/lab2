#pragma once

class ITickable {
	friend class TickEngine;

protected:
	virtual void tick() = 0;

public:
	ITickable();
	virtual ~ITickable();
};