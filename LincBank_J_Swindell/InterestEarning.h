#pragma once

// Interface Class, enforces definition for method computeInterest
class InterestEarning {
public:
	virtual float computeInterest(float years) = 0;
};