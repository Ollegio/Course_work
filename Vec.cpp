#include "Vec.h"

Vec::Vec() {
	_x = 0.0;
	_y = 0.0;
	_z = 0.0;
}
Vec::Vec(double x, double y, double z) {
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

double Vec::x() const {
	return _x;
}
double Vec::y() const {
	return _y;
}
double Vec::z() const {
	return _z;
}

double Vec::length() const {
	return sqrt(_x*_x + _y*_y + _z*_z);
}

double Vec::dot(const Vec &v) const {
	return _x*v._x + _y*v._y + _z*v._z;
}

Vec &Vec::invert() const {
	Vec result = Vec(-this->_x, -this->_y, -this->_z);
	return result;
}

Vec &Vec::add(const Vec &v) const {
	Vec result = Vec(this->_x + v._x, this->_y + v._y, this->_z + v._z);
	return result;
}

Vec &Vec::subtract(const Vec &v) const {
	Vec result;
	result._x = this->_x - v._x;
	result._y = this->_y - v._y;
	result._z = this->_z - v._z;
	return result;
}

Vec &Vec::multiply(const double &scale) const {
	Vec result = Vec(this->_x * scale, this->_y * scale, this->_z * scale);
	return result;
}

Vec &Vec::divide(const double &div) const {
	Vec result = Vec(this->_x / div, this->_y / div, this->_z / div);
	return result;
}

