#pragma once
#include "Vec.h"

class Particle {
private:
	float color[3];
	double mass, radius;
	Vec vVel, pPos, pPrev;
	int colCount;
public:
	static double meanVel;
	Particle();
	Particle(double x, double y, double z, double vx, double vy, double vz, double m, double r);
	void move(double time);
	double collidesX();
	double collidesY();
	double collidesZ();
	double collidesMaxwellDoor();
	double collides(Particle *b);
	void bounceX();
	void bounceY();
	void bounceZ();
	void bounce(Particle *b);
	int getCollisionCount() const;
	const float *getColor();
	void setColor(float r, float g, float b);
	Vec getVel();
	Vec getPos();
	void setVel(Vec v);
	void setPos(Vec v);
	const double getR();
	void updateEvents();
} ;

