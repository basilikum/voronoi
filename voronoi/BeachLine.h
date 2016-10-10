#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "Arc.h"

using namespace std;
using namespace voronoi;

class BeachLine {
private:
	shared_ptr<Arc> firstArc;
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