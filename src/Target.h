#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "PhysicsObject.h"

class Target : public PhysicsObject
{
public:
	Target();
	virtual ~Target() override;

	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

private:
	void CheckBounds();
	void Reset();
};


#endif /* defined (__TARGET__) */