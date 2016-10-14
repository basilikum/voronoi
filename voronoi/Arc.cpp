#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "Arc.h"

using namespace std;
using namespace voronoi;

Arc::Arc(const Arc& other) : site(other.site), left(nullptr), right(nullptr) {}
Arc::Arc(const Point& s, Arc* l, Arc* r) : site(s), left(l), right(r) {}
Arc* Arc::prev() const {
	return left;
}
Arc* Arc::next() const {
	return right;
}
void Arc::connectLeft(Arc* other) {
	if (left) {
		left->right = other;
		other->left = left;
	}
	other->right = this;
	left = other;
}
void Arc::connectRight(Arc* other) {
	if (right) {
		right->left = other;
		other->right = right;
	}
	other->left = this;
	right = other;
}

bool Arc::hasSameSiteAs(Arc* other) {
	return true;
}