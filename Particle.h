#pragma once
#include "Vec.h"

class Particle {
private:
	float color[3]{};
	double mass, radius;
	Vec vVel, pPos, pPrev;
	int colCount;
public:
	static double meanVel;
	Particle();
	Particle(double x, double y, double z, double vx, double vy, double vz, double m, double r);
	void move(double time);
	double collidesX() const;
	double collidesY() const;
	double collidesZ() const;
	double collidesMaxwellDoor() const;
	double collides(Particle *b) const;
	void bounceX();
	void bounceY();
	void bounceZ();
	void bounce(Particle * p);
	int getCollisionCount() const;
	const float *getColor() const;
	void setColor(float r, float g, float b);
	Vec getVel() const;
	Vec getPos() const;
	void setVel(Vec v);
	void setPos(Vec v);
	double getR() const;
	void updateEvents();
};

