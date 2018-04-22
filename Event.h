#pragma once
#include "Particle.h"

class Event {
	double eventTime;
	Particle *pA, *pB;
	int	colCountA, colCountB;
	int	type;
	
public:
	Event(double time, Particle *a, Particle *b, int t);
	int getType() const;
	double getTime() const;
	void reduceTime(double time);
	Particle *getParticle1() const;
	Particle *getParticle2() const;
	friend bool operator<(const Event &lhs, const Event &rhs) { return lhs.getTime() > rhs.getTime(); };
	bool wasSuperveningEvent() const;
};

