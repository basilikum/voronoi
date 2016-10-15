#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "PointSet.h"
#include "Voronoi.h"
#include "Arc.h"
/*
using namespace std;
using namespace voronoi;

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

class Circle {
public:
	Site center;
	double radius;
	Circle(const Site& s, double r) : center(s), radius(r) {}
};

class BeachArc {
public:
	BeachArc(const shared_ptr<BeachArc> other) : site(other->site), left(nullptr), right(nullptr) {}
	BeachArc(const shared_ptr<Site> s, shared_ptr<BeachArc> l, shared_ptr<BeachArc> r, double k) : site(s), left(l), right(r), key(k), evtKey(0) {}
	shared_ptr<Site> site;
	double key;
	double evtKey = -1;
	shared_ptr<BeachArc> left;
	shared_ptr<BeachArc> right;
};


struct Event {
	double y;
	Event(double _y) : y(_y) {}
	virtual int type() const = 0;
};

struct SiteEvent : public Event {
	const Site& site;
	SiteEvent(double _y, const Site& __site) : Event(_y), site(__site) {}
	int type() const {
		return 0;
	}
};

struct CircleEvent : public Event {
	double cx;
	double cy;
	const Arc* arc;
	CircleEvent(double _y, double _cx, double _cy, const Arc& _arc) : Event(_y), cx(_cx), cy(_cy), arc(&_arc) {}
	int type() const {
		return 1;
	}
};



class EventList {
private:
	map<double, shared_ptr<Event>> events;
	Circle get_circumcircle(shared_ptr<BeachArc> arc) {

	}
public:
	void insert(shared_ptr<BeachArc> arc) {
		shared_ptr<CircleEvent> evt;
		auto c = get_circumcircle(arc);
		double key = c.center.y + c.radius;
		if (arc->evtKey > -1) {
			evt = events[arc->evtKey];
			evt->y = key;
		}
		else {
			evt = make_shared<CircleEvent>(key, c, arc);
		}
		arc->evtKey = key;
		events[arc->evtKey] = evt;
	}
	void remove(shared_ptr<BeachArc> arc) {
		events.erase(arc->evtKey);
		arc->evtKey = -1;
	}
	map<double, shared_ptr<Event>>::const_iterator begin() {
		return events.begin();
	}
	map<double, shared_ptr<Event>>::const_iterator end() {
		return events.end();
	}
};




void get_center(double x1, double y1, double x2, double y2, double yt) {
	double dx = x2 - x1;
	double dy = y2 - y1;
	double sx = x1 + x2;
	double sy = y1 + y2;
	double c1 = x2 * y1;
	double c2 = x1 * y2;
	double q1 = x1 * x1 + y1 * y1;
	double q2 = x2 * x2 + y2 * y2;
	double dy2 = dy * dy;
	double dx2 = dx * dx;

	double d0 = -sx;
	double d1 = c1 + c2;
	double d2 = 2 * sx * sx + dy2;
	double d3 = dy * dx * sx + dy2 * sy;
	double d4 = 2 * d1 * d1 + dy * (y1 * q2 - y2 * q1);

	double x0;
	double p1 = yt * d0 + d1;
	double p2 = sqrt(yt * yt * d2 + yt * d3 + d4);
	if ((dy < 0 && p1 > 0) || (dy > 0 && p1 < 0)) {
		x0 = (p1 + p2) / -dy;
	}
	else {
		x0 = (p1 - p2) / -dy;
	}
	double y0 = (pow(x1 - x0, 2) / (y1 - yt) + (y1 + yt)) / 2;
	cout << x0 << ", " << x0 << endl;
}


class Voronoi {
private:
	map<double, unique_ptr<Event>> events;
	BeachLine beachLine;
	void loop() {
		for (const auto& it : events) {
			if (it.second->type() == 0) {
				auto evt = (const SiteEvent*)it.second.get();
				handelSiteEvent(*evt);
			}
			else {
				auto evt = (const CircleEvent*)it.second.get();
				handelCircleEvent(*evt);
			}
		}
	}
	void handelCircleEvent(const CircleEvent& evt) {

	}
	void handelSiteEvent(const SiteEvent& evt) {
		beachLine.addAt(evt.site);
	}
public:
	Voronoi() {}
	void create() {

	}
};

class BeachLine {
private:
	vector<unique_ptr<Arc>> arcs;

public:
	BeachLine() : arcs(0) {
		arcs.reserve(1000);
	}
	Arc* addAt(const Site& site) {
		auto leftArc = arcs.at(0).get();
		int leftIndex = 0;
		auto rightRightArc = leftArc->right;
		auto leftLeftArc = leftArc->left;
		auto rightArc = make_unique<Arc>(leftArc);
		auto newArc = make_unique<Arc>(site, leftArc, rightArc.get());
		rightArc->left = newArc.get();
		leftArc->right = newArc.get();
		if (rightRightArc) {
			rightRightArc->left = rightArc.get();
			rightArc->right = rightRightArc;
		}
		arcs.insert(arcs.begin() + leftIndex + 1, { move(newArc), move(rightArc) });
		return newArc.get();
	}
	void remove(Arc* arc) {
		auto leftArc = arc->left;
		auto rightArc = arc->right;
		if (leftArc && rightArc && leftArc->hasSameSiteAs(rightArc)) {
			rightArc->right = nullptr;
			rightArc->left = nullptr;
			rightArc = rightArc->right;
		}
		if (leftArc) {
			leftArc->right = rightArc;
		}
		if (rightArc) {
			rightArc->left = leftArc;
		}
		arc->right = nullptr;
		arc->left = nullptr;
	}
};
/*

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
};*/