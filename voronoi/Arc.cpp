#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "Arc.h"

using namespace std;
using namespace voronoi;

Arc::Arc(const shared_ptr<Arc> other) : site(other->site) {}
Arc::Arc(const shared_ptr<Point> s, shared_ptr<Arc> l, shared_ptr<Arc> r) : site(s), left(l), right(r) {}
shared_ptr<Arc> Arc::prev() const {
	return left;
}
shared_ptr<Arc> Arc::next() const {
	return right;
}
void Arc::connectLeft(shared_ptr<Arc> other) {
	if (left) {
		left->right = other;
		other->left = left;
	}
	other->right = shared_from_this();
	left = other;
}
void Arc::connectRight(shared_ptr<Arc> other) {
	if (right) {
		right->left = other;
		other->right = right;
	}
	other->left = shared_from_this();
	right = other;
}

bool Arc::hasSameSiteAs(shared_ptr<Arc> other) {
	return other->site == site;
}