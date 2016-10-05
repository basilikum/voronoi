#pragma once
#include <iostream>
#include "PointSet.h"
#include "Voronoi.h"

using namespace std;

Voronoi::Voronoi() : _set(PointSet()) {}
Voronoi::Voronoi(int num) : _set(PointSet(num)) {}
vector<Edge> Voronoi::compute(const PointSet& set) const {
	for (const auto& p : set) {

	}
}

class VoronoiTriple {
private:
	VoronoiSite *sites[3];
	BeachLine *beachLine;
	VoronoiCircleEvent *circleEvent;
};

class VoronoiEvent {
protected:
	double _y;
};

class VoronoiSiteEvent: public VoronoiEvent {
protected:
	VoronoiSite *site;
};

class VoronoiCircleEvent : public VoronoiEvent {
protected:
	VoronoiTriple *triple;
};

class VoronoiSite {
private:
	double _x, _y;

};

class BeachLine {
private:
	vector<Point> points;
	vector<Point[3]> triples;
};