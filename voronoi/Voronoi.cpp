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

class Site {
public:
	double x, y;
	Site(double _x, double _y) : x(_x), y(_y) {}
};

class BeachArc {
public:
	BeachArc(shared_ptr<Site> s, shared_ptr<BeachArc> l, shared_ptr<BeachArc> r, double k) : site(s), left(l), right(r), key(k), evtKey(0) {}
	shared_ptr<Site> site;
	double key;
	double evtKey;
	shared_ptr<BeachArc> left;
	shared_ptr<BeachArc> right;
};

class BeachLine {
private:
	map<double, shared_ptr<BeachArc>> arcs;
	map<double, shared_ptr<BeachArc>> triples;
	map<double, shared_ptr<BeachArc>> events;
public:
	BeachLine() {

	}
	shared_ptr<BeachArc> findArc(double x) {

	}

	void get_circumcircle(shared_ptr<BeachArc> arc) {

	}

	void update_or_create_circle_event(shared_ptr<BeachArc> arc) {
		double r, x, y;
		arc->evtKey = y + r;
	}

	void deleteArc(shared_ptr<BeachArc> oldArc) {
		removeArc(oldArc->key);
		if (oldArc->left) {
			auto leftArc = oldArc->left;
			if (oldArc->right) {
				auto rightArc = oldArc->right;
				if (rightArc->site == leftArc->site) {
					removeArc(rightArc->key);
					leftArc->right = rightArc->right;
					if (rightArc->right) {
						rightArc->right->left = leftArc;
					}
					if (leftArc->left) {
						//triple and event definitely has existed
						if (leftArc->right && leftArc->left->site != leftArc->right->site) {
							//triple remains
							update_or_create_circle_event(leftArc);
						}
						else {
							triples.erase(leftArc->key);
							events.erase(leftArc->evtKey);
						}
					}
				}
				else {
					leftArc->right = rightArc;
					rightArc->left = leftArc;
					if (leftArc->left) {
						triples[leftArc->key] = leftArc;
						update_or_create_circle_event(leftArc);
					}
					if (rightArc->right) {
						triples[rightArc->key] = rightArc;
						update_or_create_circle_event(rightArc);
					}
				}
			}
			else {
				leftArc->right = nullptr;
				triples.erase(leftArc->key);
				events.erase(leftArc->evtKey);
			}
		}
		else if (oldArc->right) {
			auto rightArc = oldArc->right;
			rightArc->left = nullptr;
			triples.erase(rightArc->key);
			events.erase(rightArc->evtKey);
		}
		else {
			//no neighbors
		}
	}

	void splitArc(shared_ptr<BeachArc> oldArc, shared_ptr<Site> site) {
		removeArc(oldArc->key);
		double leftKey = 0, rightKey = 1;
		if (oldArc->left) {
			leftKey = oldArc->left->key;
		}
		if (oldArc->right) {
			rightKey = oldArc->right->key;
		}
		auto leftArc = make_shared<BeachArc>(oldArc->site, oldArc->left, nullptr, (leftKey + oldArc->key) / 2);
		auto rightArc = make_shared<BeachArc>(oldArc->site, nullptr, oldArc->right, (rightKey + oldArc->key) / 2);
		auto middleArc = make_shared<BeachArc>(site, leftArc, rightArc, oldArc->key);
		leftArc->right = middleArc;
		rightArc->left = middleArc;
		arcs[leftArc->key] = leftArc;
		arcs[rightArc->key] = rightArc;
		arcs[middleArc->key] = middleArc;
		if (leftArc->left) {
			triples[leftArc->key] = leftArc;
			update_or_create_circle_event(leftArc);
		}
		if (rightArc->right) {
			triples[rightArc->key] = rightArc;
			update_or_create_circle_event(rightArc);
		}
	}

	void removeArc(double key) {
		triples.erase(key);
		events.erase(key);
		arcs.erase(key);
	}
};