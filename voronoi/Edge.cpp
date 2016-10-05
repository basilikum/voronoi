#pragma once
#include <iostream>
#include "Edge.h"
#include "Point.h"
using namespace std;

Edge::Edge() : _p1(Point()), _p2(Point()) {
	cout << "E empty " << *this << endl;
}
Edge::Edge(double x1, double y1, double x2, double y2) : _p1(Point(x1, y1)), _p2(Point(x2, y2)) {
	cout << "E init nums " << *this << endl;
}
Edge::Edge(const Point& p1, const Point& p2) : _p1(p1), _p2(p2) {
	cout << "E init points " << *this << endl;
}
Edge::Edge(const Edge& other) : _p1(Point(other._p1)), _p2(Point(other._p2)) {
	cout << "E copy " << *this << endl;
}
Edge::Edge(Edge&& other) {
	swap(other);
	cout << "E move " << *this << endl;
}
Edge& Edge::operator=(Edge other) {
	swap(other);
	cout << "E = " << *this << endl;
	return *this;
}
void Edge::swap(Edge& other) {
	std::swap(_p1, other._p1);
	std::swap(_p2, other._p2);
}
const Point& Edge::p1() const {
	return _p1;
}
void Edge::p1(const Point& p1) {
	_p1 = p1;
}
const Point& Edge::p2() const {
	return _p2;
}
void Edge::p2(const Point& p2) {
	_p2 = p2;
}
double Edge::length() const {
	return _p1.getDistance(_p2);
}
std::ostream& operator<<(std::ostream &strm, const Edge& edge) {
	return strm << "E((" << edge.p1().x() << ", " << edge.p1().y() << ")->(" << edge.p2().x() << ", " << edge.p2().y() << "))";
}
