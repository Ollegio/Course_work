#include "Event.h"
#include "Particle.h"

Event::Event(double time, Particle *a, Particle *b, int t) {
	pA = a, pB = b, type = t, eventTime = time;
	if (t == 4)
		colCountA = a->getCollisionCount(), colCountB = b->getCollisionCount();
	if (t == 1 || t == 2 || t == 3)
		colCountA = a->getCollisionCount();
}

int Event::getType() const {
	return type;
}

double Event::getTime() const {
	return this->eventTime;
}

void Event::reduceTime(double time) {
	eventTime -= time;
}

Particle *Event::getParticle1() {
	return pA;
}

Particle *Event::getParticle2() {
	return pB;
}

bool Event::wasSuperveningEvent() {
	if (type == 4)
		return (colCountA != this->pA->getCollisionCount() || colCountB != this->pB->getCollisionCount());
	if (type == 1 || type == 2 || type == 3)
		return colCountA != this->pA->getCollisionCount();
	else
		return false;
}
