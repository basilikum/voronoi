#pragma once
#include <map>
#include <memory>
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



class BeachArc {
public:
	BeachArc(double _x, double _y) : x(_x), y(_y), left(nullptr), right(nullptr), key(0) {}
	BeachArc(double _x, double _y, shared_ptr<BeachArc> l, shared_ptr<BeachArc> r, double k) : x(_x), y(_y), left(l), right(r), key(k) {}
	double x, y;
	double key;
	shared_ptr<BeachArc> left;
	shared_ptr<BeachArc> right;
};

class BeachLine {
private:
	map<double, shared_ptr<BeachArc>> arcs;
	map<double, shared_ptr<BeachArc>> triples;
public:
	BeachLine() {

	}
	shared_ptr<BeachArc> findArc(double x) {

	}

	void deleteArc(shared_ptr<BeachArc> oldArc) {
		removeArc(oldArc->key);
		if (oldArc->left) {
			auto leftArc = oldArc->left;
			if (oldArc->right) {
				auto rightArc = oldArc->right;
				if (rightArc->x == leftArc->x && rightArc->y == leftArc->y) {
					removeArc(rightArc->key);
					leftArc->right = rightArc->right;
					if (rightArc->right) {
						rightArc->right->left = leftArc;
					}
					if (leftArc->left && leftArc->right && (leftArc->left->x != leftArc->right->x || leftArc->left->y != leftArc->right->y)) {
						triples[leftArc->key] = leftArc;
						//add or update up event
					}
					else {
						triples.erase(leftArc->key);
						//clean up event
					}
				}
				else {
					leftArc->right = rightArc;
					rightArc->left = leftArc;
					if (leftArc->left) {
						triples[leftArc->key] = leftArc;
						//add or update up event
					}
					if (rightArc->right) {
						triples[rightArc->key] = rightArc;
						//add or update up event
					}
				}
			}
			else {
				leftArc->right = nullptr;
				triples.erase(leftArc->key);
				//clean up event
			}
		}
		else if (oldArc->right) {
			auto rightArc = oldArc->right;
			rightArc->left = nullptr;
			triples.erase(rightArc->key);
			//clean up event
		}
		else {
			//no neighbors
		}
	}

	void splitArc(shared_ptr<BeachArc> oldArc, double x, double y) {
		removeArc(oldArc->key);
		double leftKey = 0, rightKey = 1;
		if (oldArc->left) {
			leftKey = oldArc->left->key;
		}
		if (oldArc->right) {
			rightKey = oldArc->right->key;
		}
		auto leftArc = make_shared<BeachArc>(oldArc->x, oldArc->y, oldArc->left, nullptr, (leftKey + oldArc->key) / 2);
		auto rightArc = make_shared<BeachArc>(oldArc->x, oldArc->y, nullptr, oldArc->right, (rightKey + oldArc->key) / 2);
		auto middleArc = make_shared<BeachArc>(x, y, leftArc, rightArc, oldArc->key);
		leftArc->right = middleArc;
		rightArc->left = middleArc;
		arcs[leftArc->key] = leftArc;
		arcs[rightArc->key] = rightArc;
		arcs[middleArc->key] = middleArc;
		if (leftArc->left) {
			triples[leftArc->key] = leftArc;
		}
		if (rightArc->right) {
			triples[rightArc->key] = rightArc;
		}
	}

	void removeArc(double key) {
		triples.erase(key);
		//clean up event
		arcs.erase(key);
	}
};