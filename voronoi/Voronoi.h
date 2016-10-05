#pragma once
#include <iostream>
#include "PointSet.h"
#include "Edge.h"
using namespace std;

class Voronoi {
private:
	PointSet _set;
public:
	Voronoi();
	Voronoi(int num);
	vector<Edge> compute(const PointSet& set) const;
};
