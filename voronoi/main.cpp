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


int main() {

	cout << "#######" << endl;
	for (int i = 0; i < 100000000; i++) {
		get_breakpoint1(-1.5, 1, 0.707107, 1.707107);
	}
	cout << "#######" << endl;
	for (int i = 0; i < 100000000; i++) {
		get_breakpoint2(0.707107, 2.20711, 3.26777, 5.37132, 14.5407, 9.16942, -2.345);
	}
	cout << "#######" << endl;

	/*
	srand(time(0));
	Point p1(2, 3);
	Point p2(5, 6);
	Edge e1(p1, p2);
	Edge e2 = e1;*/
	int i;
	cin >> i;
}