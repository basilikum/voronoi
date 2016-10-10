#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "Point.h"

using namespace std;

namespace voronoi {
	class Arc : public enable_shared_from_this<Arc> {
	private:
		shared_ptr<Point> site;
		double evtKey = -1;
	public:
		shared_ptr<Arc> left;
		shared_ptr<Arc> right;
		Arc(const shared_ptr<Arc> other);
		Arc(const shared_ptr<Point> s, shared_ptr<Arc> l, shared_ptr<Arc> r);
		shared_ptr<Arc> prev() const;
		shared_ptr<Arc> next() const;
		void connectLeft(shared_ptr<Arc> other);
		void connectRight(shared_ptr<Arc> other);
		void setEvt(double key);
		void unsetEvt();
		bool hasSameSiteAs(shared_ptr<Arc> other);
	};
}