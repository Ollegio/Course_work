#pragma once
#include <cmath>

const double EPSILON = 1.0e-8;

class Vec {
	double _x;
	double _y;
	double _z;
public:
	Vec();
	Vec(double x, double y, double z);
	double x() const;
	double y() const;
	double z() const;
	double length() const;
	double dot(const Vec &v) const;
	Vec add(const Vec &v) const;
	Vec subtract(const Vec &v) const;
	Vec invert() const;
	Vec multiply(const double &scale) const;
	Vec divide(const double & div) const;

	friend double dot(const Vec &v1, const Vec &v2) {
		return v1.dot(v2);
	}

	friend Vec operator-(const Vec &v) {
		return v.invert();
	}

	friend Vec operator-(const Vec &v1, const Vec &v2)  {
		return v1.subtract(v2);
	}

	friend Vec operator+(const Vec &v1, const Vec &v2) {
		return v1.add(v2);
	}

	friend Vec operator*(const Vec &v, const double &scale) {
		return v.multiply(scale);
	}
	friend Vec operator*(const double &scale, const Vec &v) {
		return v.multiply(scale);
	}

	friend Vec operator/(const Vec &v,const double &div) {
		return v.divide(div);
	}

	friend bool operator==(const Vec &v1, const Vec &v2) {
		return (fabs(v1.x() - v2.x()) < EPSILON && fabs(v1.y() - v2.y()) < EPSILON && fabs(v1.z() - v2.z()) < EPSILON);
	}
};
