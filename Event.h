#pragma once
#include "Particle.h"

class Event {
private:
	double eventTime;
	Particle *pA, *pB;
	int	colCountA, colCountB;
	int	type;
	
public:
	Event(double time, Particle *a, Particle *b, int type);
	int getType() const;
	double getTime() const;
	void reduceTime(double time);
	Particle *getParticle1();
	Particle *getParticle2();
	friend bool operator<(const Event &lhs, const Event &rhs) { return lhs.getTime() > rhs.getTime(); };
	bool wasSuperveningEvent();
};

