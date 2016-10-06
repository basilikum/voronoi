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

int main() {
	map<int, char> m;
	m.insert(pair<int, char>(1, 'a'));
	m.insert(pair<int, char>(3, 'b'));
	m.insert(pair<int, char>(2, 'c'));
	m.erase(2);
	m.erase(4);
	for (const auto& p : m) {
		cout << p.first << " ==> " << p.second << endl;
	}




	/*
	srand(time(0));
	Point p1(2, 3);
	Point p2(5, 6);
	Edge e1(p1, p2);
	Edge e2 = e1;*/
	int i;
	cin >> i;
}