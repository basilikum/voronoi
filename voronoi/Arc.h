#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "Point.h"

using namespace std;

namespace voronoi {
	class Arc {
	private:
		const Point& site;
		double evtKey = -1;
	public:
		Arc* left;
		Arc* right;
		Arc(const Arc& other);
		Arc(const Point* s, Arc* l, Arc* r);
		Arc* prev() const;
		Arc* next() const;
		void connectLeft(Arc* other);
		void connectRight(Arc* other);
		void setEvt(double key);
		void unsetEvt();
		bool hasSameSiteAs(Arc* other);
	};
}