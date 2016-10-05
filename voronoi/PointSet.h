#pragma once
#include <iostream>
#include <vector>
#include "Point.h";
using namespace std;

class PointSet {
private:
	vector<Point> data;
public:
	PointSet();
	PointSet(int num);
	vector<Point>::const_iterator begin() const;
	vector<Point>::const_iterator end() const;
};