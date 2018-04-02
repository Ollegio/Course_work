#include "Particle.h"
#include "Vec.h"
#include "Event.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
using namespace std::chrono;

Vec vInitVel = Vec(0.0, 0.0, 0.0);
std::vector<Event> pq;
std::priority_queue<Event> ct;
int PARTICLES_COUNT;
Particle particles[];
double currentTime;
double Particle::meanVel;

Particle::Particle() {
	vVel = Vec();
	pPos = Vec();
	mass = 1.0;
	radius = 10.0;
	colCount = 0;
}

Particle::Particle(double x, double y, double z, double vx, double vy, double vz, double m, double r) {
	vVel = Vec(vx, vy, vz);
	pPos = Vec(x, y, z);
	mass = m;
	radius = r;
	colCount = 0;
}

void Particle::move(double time) {
	setPos(getPos() + getVel() * time);
}

double Particle::collidesX() {
	double res;
	if (getVel().x() > EPSILON)
		res = (300 - radius - getPos().x()) / getVel().x();
	else
		if (getVel().x() < -EPSILON)
			res = (-300 + radius - getPos().x()) / getVel().x();
		else
			res = -1.0;
	return res;
}

double Particle::collidesY() {
	double res;
	if (getVel().y() > EPSILON)
		res = (300 - radius - getPos().y()) / getVel().y();
	else
		if (getVel().y() < -EPSILON)
			res = (-300 + radius - getPos().y()) / getVel().y();
		else
			res = -1.0;
	return res;
}

double Particle::collidesZ() {
	double res;
	if (getVel().z() > EPSILON)
		res = (300 - radius - getPos().z()) / getVel().z();
	else
		if (getVel().z() < -EPSILON)
			res = (-300 + radius - getPos().z()) / getVel().z();
		else
			res = -1.0;
	return res;
}

double Particle::collidesMaxwellDoor() {
	double res;
	if (getPos().x() < 0 && getVel().length() < meanVel && getVel().x() > EPSILON)
		res = (-radius - getPos().x()) / getVel().x();
	else
		if (getPos().x() > 0 && getVel().length() > meanVel && getVel().x() < -EPSILON)
			res = (radius - getPos().x()) / getVel().x();
		else
			res = -1.0;
	return res;
}

double Particle::collides(Particle *b) {
	Vec dr = getPos() - b->getPos(),
		dv = getVel() - b->getVel();
	double
		r2 = dot(dr, dr),
		v2 = dot(dv, dv),
		vr = dot(dv, dr);
	if (vr > -EPSILON)
		return -1.0;
	double d = pow(vr, 2) - v2 * (r2 - pow((radius)+b->radius, 2));
	if (d < EPSILON)
		return -1.0;

	double res = -((vr + sqrt(d)) / v2);
	return res;
}

void Particle::bounceX() {
	colCount++;
	setVel(Vec(-getVel().x(), getVel().y(), getVel().z()));
}

void Particle::bounceY() {
	colCount++;
	setVel(Vec(getVel().x(), -getVel().y(), getVel().z()));
}

void Particle::bounceZ(){
	colCount++;
	setVel(Vec(getVel().x(), getVel().y(), -getVel().z()));
}

void Particle::bounce(Particle *p) {
	Vec
		v1 = this->getVel(),
		v2 = p->getVel(),
		p1 = this->getPos(),
		p2 = p->getPos();
	double
		m1 = this->mass,
		m2 = p->mass;

	this->setVel(v1 - 2.0 * m2 / (m1 + m2) * dot(v1 - v2, p1 - p2) * (p1 - p2) / pow((p1 - p2).length(), 2.0));
	p->setVel(v2 - 2.0 * m1 / (m1 + m2) * dot(v2 - v1, p2 - p1) * (p2 - p1) / pow((p2 - p1).length(), 2.0));
	colCount++;
	p->colCount++;
}

int Particle::getCollisionCount() const {
	return colCount;
}

const float *Particle::getColor() {
	return &this->color[0];
}

void Particle::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

Vec Particle::getVel() {
	return vVel;
}

Vec Particle::getPos() {
	return pPos;
}

void Particle::setVel(Vec v) {
	vVel = v;
}

void Particle::setPos(Vec v) {
	pPos = v;
}

const double Particle::getR() {
	return radius;
}

void Particle::updateEvents() {
	double xTime = this->collidesX(),
		yTime = this->collidesY(),
		zTime = this->collidesZ();
	if (Particle::meanVel != 0) {
		double mTime = this->collidesMaxwellDoor();
		if (mTime != -1.0) {
			ct.push(Event(currentTime + mTime, this, nullptr, 1));
		}
	}
	if (xTime != -1.0) {
		ct.push(Event(currentTime + xTime, this, nullptr, 1));
	}
	if (yTime != -1.0) {
		ct.push(Event(currentTime + yTime, this, nullptr, 2));
	}
	if (zTime != -1.0) {
		ct.push(Event(currentTime + zTime, this, nullptr, 3));
	}
	for (int j = 0; j < PARTICLES_COUNT; j++) {
		if (this != &particles[j]) {
			double abTime = this->collides(&particles[j]);
			if (abTime != -1.0) {
				ct.push(Event(currentTime + abTime, this, &particles[j], 4));
			}	
		}
	}
}