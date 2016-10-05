#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include "PointSet.h";
#include "Point.h";
using namespace std;

struct compare {
	inline bool operator() (const Point& p1, const Point& p2) {
		return p1.y() < p2.y();
	}
};

PointSet::PointSet() : data(0) {}

PointSet::PointSet(int num) : data(num) {
	for (; num > 0; num--) {
		data[num - 1] = Point(
			(double)rand() / RAND_MAX,
			(double)rand() / RAND_MAX
		);
	}
	sort(data.begin(), data.end(), compare());
}
vector<Point>::const_iterator PointSet::begin() const {
	return data.begin();
}
vector<Point>::const_iterator PointSet::end() const {
	return data.end();
}
