#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "PointSet.h"
#include "Voronoi.h"

using namespace std;
/*
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


class Event {
public:
	double y;
	bool site;
	Event(double _y) : y(_y), site(true) {}
	Event(double _y, bool _s) : y(_y), site(_s) {}
};

class SiteEvent : public Event {
private:
	shared_ptr<Site> site;
};

class CircleEvent : public Event {
private:
	shared_ptr<BeachArc> arc;
	Circle circle;
public:
	CircleEvent(double y, const Circle& c, shared_ptr<BeachArc> a) : Event(y, false), circle(c), arc(a) {}
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


class Voronoi {
private:
	BeachLine bl;
	EventList el;
public:

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



class BeachLine {
private:
	shared_ptr<BeachArc> firstArc;
	EventList el;
public:
	BeachLine() {}
	void iterate() {
		for (auto it = el.begin(); it != el.end(); it++) {
			if (it->second->site) {
				auto evt = static_pointer_cast<SiteEvent>(it->second);
			}
			else {
				auto evt = static_pointer_cast<CircleEvent>(it->second);
			}
		}
	}
	void split(shared_ptr<BeachArc> newArc, shared_ptr<BeachArc> leftArc) {
		auto rightRightArc = leftArc->right;
		auto leftLeftArc = leftArc->left;
		auto rightArc = make_shared<BeachArc>(leftArc);
		if (rightRightArc) {
			rightRightArc->left = rightArc;
			rightArc->right = rightRightArc;
		}
		rightArc->left = newArc;
		newArc->right = rightArc;
		newArc->left = leftArc;
		leftArc->right = newArc;
	}
	void remove(shared_ptr<BeachArc> arc) {
		auto leftArc = arc->left;
		auto rightArc = arc->right;
		if (leftArc && rightArc && leftArc->site == rightArc->site) {
			rightArc->right = nullptr;
			rightArc->left = nullptr;
			rightArc = rightArc->right;
		}
		if (leftArc) {
			leftArc->right = rightArc;
		}
		else {
			firstArc = rightArc;
		}
		if (rightArc) {
			rightArc->left = leftArc;
		}
		arc->right = nullptr;
		arc->left = nullptr;
	}
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
};*/