#pragma once

class ITickable {
	friend class TickEngine;

protected:
	virtual void tick(float time) = 0;

public:
	ITickable();
	virtual ~ITickable();
};