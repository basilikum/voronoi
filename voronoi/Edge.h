#pragma once
#include <iostream>
#include "Point.h"
using namespace std;

class Edge {
private:
	Point _p1, _p2;
	void swap(Edge& other);
public:
	Edge();
	Edge(double x1, double y1, double x2, double y2);
	Edge(const Point& p1, const Point& p2);
	Edge(const Edge& other);
	Edge(Edge&& other);
	Edge& operator=(Edge other);
	const Point& p1() const;
	void p1(const Point& p1);
	const Point& p2() const;
	void p2(const Point& p2);
	double length() const;
};
std::ostream& operator<<(std::ostream &strm, const Edge& edge);