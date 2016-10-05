#include <iostream>
#include "Point.h";
using namespace std;

Point::Point() : _x(0), _y(0) {
	cout << "P empty " << *this << endl;
};
Point::Point(double x, double y) : _x(x), _y(y) {
	cout << "P init " << *this << endl;
};
Point::Point(const Point& other) : _x(other._x), _y(other._y) {
	cout << "P copy " << *this << endl;
};
Point::Point(Point&& other) : _x(0), _y(0) {
	swap(other);
	cout << "P move " << *this << endl;
};
Point& Point::operator=(const Point& other) {
	_x = other._x;
	_y = other._y;
	cout << "P = " << *this << endl;
	return *this;
}
Point Point::operator+(const Point& other) const {
	Point p(_x + other._x, _y + other._y);
	cout << "P + " << *this << endl;
	return p;
}
Point Point::operator-(const Point& other) const {
	Point p(_x - other._x, _y - other._y);
	cout << "P - " << *this << endl;
	return p;
}
Point& Point::operator+=(const Point& other) {
	_x += other._x;
	_y += other._y;
	cout << "P += " << *this << endl;
	return *this;
}
Point& Point::operator-=(const Point& other) {
	_x -= other._x;
	_y -= other._y;
	cout << "P -= " << *this << endl;
	return *this;
}
void Point::swap(Point& other) {
	std::swap(_x, other._x);
	std::swap(_y, other._y);
}
double Point::x() const {
	return _x;
}
void Point::x(double x) {
	_x = x;
}
double Point::y() const {
	return _y;
}
void Point::y(double y) {
	_y = y;
}
double Point::getDistance(const Point& other) const {
	return sqrt(pow(other._x - _x, 2) + pow(other._y - _y, 2));
}

std::ostream& operator<<(std::ostream &strm, const Point& point) {
	return strm << "P(" << point.x() << ", " << point.y() << ")";
}