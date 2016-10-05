#pragma once
#include <iostream>
using namespace std;

class Point {
private:
	double _x, _y;
	void swap(Point& other);
public:
	Point();
	Point(double x, double y);
	Point(const Point& other);
	Point(Point&& other);
	Point& operator=(const Point& other);
	Point operator+(const Point& other) const;
	Point operator-(const Point& other) const;
	Point& operator+=(const Point& other);
	Point& operator-=(const Point& other);
	double x() const;
	void x(double x);
	double y() const;
	void y(double y);
	double getDistance(const Point& other) const;
	friend class Edge;
};
std::ostream& operator<<(std::ostream &strm, const Point& point);