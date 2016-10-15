#pragma once
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include "Point.h"
#include "PointSet.h"
#include "Edge.h"

using namespace std;

float get_breakpoint_f(float x1, float y1, float x2, float y2, float yt) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float c1 = x2 * y1;
	float c2 = x1 * y2;

	float d0 = dx;
	float d1 = c1 - c2;
	float d2 = dx * dx + dy * dy;
	float d3 = (y1 + y2) * d2;
	float d4 = (y1 * y2) * d2;

	//7* 5+

	float p1 = yt * d0 - d1;
	float p2 = sqrt(yt * yt * d2 + yt * d3 + d4);
	//cout << d0 << " " << d1 << " " << d2 << " " << d3 << " " << d4 << endl;
	if ((dy < 0 && p1 < 0) || (dy > 0 && p1 > 0)) {
		return (p1 - p2) / dy;
	}
	else {
		return (p1 + p2) / dy;
	}

	//6* 4+

	//double y0 = (pow(x1 - x0, 2) / (y1 - yt) + (y1 + yt)) / 2;
	//
	//cout << x0 << ", " << y0 << endl;
}


double get_breakpoint(double x1, double y1, double x2, double y2, double yt) {
	double dx = x2 - x1;
	double dy = y2 - y1;
	double c1 = x2 * y1;
	double c2 = x1 * y2;

	double d0 = dx;
	double d1 = c1 - c2;
	double d2 = dx * dx + dy * dy;
	double d3 = (y1 + y2) * d2;
	double d4 = (y1 * y2) * d2;

	//7* 5+

	double p1 = yt * d0 - d1;
	double p2 = sqrt(yt * yt * d2 + yt * d3 + d4);
	cout << dy << " " << d0 << " " << d1 << " " << d2 << " " << d3 << " " << d4 << endl;
	if ((dy < 0 && p1 < 0) || (dy > 0 && p1 > 0)) {
		return (p1 - p2) / dy;
	}
	else {
		return (p1 + p2) / dy;
	}

	//6* 4+

	//double y0 = (pow(x1 - x0, 2) / (y1 - yt) + (y1 + yt)) / 2;
	//
	//cout << x0 << ", " << y0 << endl;
}

void get_breakpoint1(double x1, double y1, double x2, double y2) {
	double dx = x2 - x1;
	double dy = y2 - y1;
	double c1 = x2 * y1;
	double c2 = x1 * y2;

	double d0 = dx;
	double d1 = c1 - c2;
	double d2 = dx * dx + dy * dy;
	double d3 = (y1 + y2) * d2;
	double d4 = (y1 * y2) * d2;
}

double get_breakpoint2(double dy, double d0, double d1, double d2, double d3, double d4, double yt) {
	double p1 = yt * d0 - d1;
	double p2 = sqrt(yt * yt * d2 + yt * d3 + d4);
	if ((dy < 0 && p1 < 0) || (dy > 0 && p1 > 0)) {
		return (p1 - p2) / dy;
	}
	else {
		return (p1 + p2) / dy;
	}
}

double get_center(double x1, double y1, double x2, double y2, double x3, double y3) {
	double a1 = x1 * x1 + y1 * y1;
	double a2 = x2 * x2 + y2 * y2;
	double a3 = x3 * x3 + y3 * y3;
	double dx1 = x3 - x2;
	double dx2 = x1 - x3;
	double dx3 = x2 - x1;
	double dy1 = y2 - y3;
	double dy2 = y3 - y1;
	double dy3 = y1 - y2;
	double det = 1 / (2 * (y1 * dx1 + y2 * dx2 + y3 * dx3));
	double yt = det * (a1 * dx1 + a2 * dx2 + a3 * dx3);
	double xt = det * (a1 * dy1 + a2 * dy2 + a3 * dy3);
	double dy0 = yt - y1;
	double dx0 = xt - x1;
	double r = sqrt(dy0 * dy0 + dx0 * dx0);
	return yt + r;
	//19* 1/ 15+
}

map<int, Point*> m;

void b(Point& p) {
	p.x(10);
}

void a(Point& p) {
	b(p);
}



class Item {
public:
	Item(): value(0), next(nullptr), prev(nullptr) {}
	Item(int v) : value(v), next(nullptr), prev(nullptr) {}
	int value;
	shared_ptr<Item> next;
	shared_ptr<Item> prev;
};

class ItemList1 {
private:
	int _length;
	unordered_map<int, unique_ptr<Item>> items;

public:
	ItemList1() : _length(0) {}
	Item* operator[](int index) {
		return items[index].get();
	}
	int length() const {
		return _length;
	}
	void add(int v, int i) {
		items.emplace(i, make_unique<Item>(v));
		_length++;
	}
};

class ItemList2 {
private:
	int _length;
	vector<unique_ptr<Item>> items;

public:
	ItemList2() : _length(0) {}
	Item* operator[](int index) {
		return items[index].get();
	}
	int length() const {
		return _length;
	}
	void add(int v, int i) {
		items.emplace(items.begin() + i, make_unique<Item>(v));
		_length++;
	}
};

int main() {
	vector<unique_ptr<Item>> vec(0);
	vec.reserve(100);
	vec.emplace(vec.begin(), make_unique<Item>(0));

	/*
	double x1 = (double)rand() / RAND_MAX;
	double y1 = (double)rand() / RAND_MAX;
	double x2 = (double)rand() / RAND_MAX;
	double y2 = (double)rand() / RAND_MAX;
	double x3 = (double)rand() / RAND_MAX;
	double y3 = (double)rand() / RAND_MAX;
	cout << "#######" << endl;
	double r1, r2;
	for (int i = 0; i < 500000000; i++) {
		get_breakpoint1(x1, y1, x2, y2);
	}
	cout << "#######" << endl;
	for (int i = 0; i < 500000000; i++) {
		r2 = get_breakpoint2(x1, y1, x2, y2, x3, y3, x2);
	}
	cout << "####### " << endl;
	*/
	/*
	srand(time(0));
	Point p1(2, 3);
	Point p2(5, 6);
	Edge e1(p1, p2);
	Edge e2 = e1;*/
	int i;
	cin >> i;
}