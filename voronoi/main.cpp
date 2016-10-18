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

struct node // the structure for representing tree nodes 
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

node* rotateright(node* p) // the right rotation round p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // the left rotation round q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // p node balance
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // no balance needed
}

node* bts_insert(node* p, int k) // k key insertion in the tree with p root  
{
	if (!p) return new node(k);
	if (k<p->key)
		p->left = bts_insert(p->left, k);
	else
		p->right = bts_insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // searching the node with the minimal key in p tree  
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p) // deleting the node with the minimal key from p tree 
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* bts_remove(node* p, int k) // k key deletion from p tree
{
	if (!p) return 0;
	if (k < p->key)
		p->left = bts_remove(p->left, k);
	else if (k > p->key)
		p->right = bts_remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}


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
	Item* prev;
	Item* next;
	double x, y;
	double value;
	int index = 0;
	Item(): value(0), x(1.5), y(-1.5), next(nullptr), prev(nullptr) {}
	Item(double v) : value(v), x(1.5), y(-1.5), next(nullptr), prev(nullptr) {}
	void update(const Item* other) {
		x = other->x;
		y = other->y;
		value = other->value;
		prev = other->prev;
		next = other->next;
	}
};

class ItemList1 {
private:
	int _length;
	vector<Item> items;

public:
	ItemList1() : _length(0) {
		items.reserve(20000);
		cout << "INI" << endl;
	}
	Item* operator[](int index) {
		return &items[index];
	}
	int length() const {
		return _length;
	}
	Item* get(int idx) {
		return &items[idx];
	}
	void insert(double v, int idx) {
		items.emplace(items.begin() + idx, Item(v));
		_length++;
	}
	void remove(int idx) {
		items.erase(items.begin() + idx);
	}
};

class ItemList2 {
private:
	int _length;
	unordered_map<double, unique_ptr<Item>> items;
	vector<double> keys;
public:
	ItemList2() : _length(0) {
		cout << "INI" << endl;
	}
	Item* operator[](int index) {
		return items[index].get();
	}
	int length() const {
		return _length;
	}
	void insert(double v, double key) {
		auto it = lower_bound(keys.begin(), keys.end(), key);
		keys.insert(it, key);
		items[key] = make_unique<Item>(v);
		_length++;
	}
	void remove(double key) {
		items.erase(key);
		auto pr = equal_range(keys.begin(), keys.end(), key);
		keys.erase(pr.first, pr.second);
	}
	Item* get(int idx) {
		return items[keys[idx]].get();
	}
	void print() {
		for (const auto& a : keys) {
			cout << a << endl;
		}
	}
};


class ItemList3 {
private:
	int _length;
	map<double, unique_ptr<Item>> items;
	vector<double> keys;
public:
	ItemList3() : _length(0) {
		cout << "INI" << endl;
	}
	Item* operator[](int index) {
		return items[index].get();
	}
	int length() const {
		return _length;
	}
	void insert(double v, double key) {
		auto it = lower_bound(keys.begin(), keys.end(), key);
		keys.insert(it, key);
		items[key] = make_unique<Item>(v);
		_length++;
	}
	void remove(double key) {
		items.erase(key);
		auto pr = equal_range(keys.begin(), keys.end(), key);
		keys.erase(pr.first, pr.second);
		_length--;
	}
	Item* get(int idx) {
		return items[keys[idx]].get();
	}
	void print() {
		for (const auto& a : keys) {
			cout << a << endl;
		}
	}
};

class ItemList4 {
private:
	int _length;
	int _lastIdx = -1;
	vector<Item> items;
	vector<int> indices;
public:
	ItemList4() : _length(0) {
		items.reserve(20000);
		indices.reserve(20000);
	}
	Item* operator[](int index) {
		return &items[index];
	}
	int length() const {
		return _length;
	}
	void insert(double v, int idx) {
		indices.insert(indices.begin() + idx, _length);
		_lastIdx = idx;
		items.push_back(Item(v));
		_length++;
	}
	void remove(int idx) {
		int itemIdx = indices[idx];

		items[itemIdx] = items[items.size() - 1];
		items.pop_back();
		indices.erase(indices.begin() + idx);

		if (itemIdx < _length - 1) {
			if (_lastIdx > -1) {
				indices[_lastIdx] = itemIdx;
				_lastIdx = -1;
			}
			else {
				auto it = find(indices.begin(), indices.end(), _length - 1);
				*it = itemIdx;
			}
		}
		_length--;
	}
	Item* get(int idx) {
		return &items[indices[idx]];
	}
};

class ItemList5 {
private:
	int _length;
	int _lastIdx = -1;
	vector<unique_ptr<Item>> items;
	vector<int> indices;
public:
	ItemList5() : _length(0) {
		items.reserve(20000);
		indices.reserve(20000);
	}
	Item* operator[](int index) {
		return items[index].get();
	}
	int length() const {
		return _length;
	}
	void insert(double v, int idx) {
		indices.insert(indices.begin() + idx, _length);
		_lastIdx = idx;
		items.push_back(make_unique<Item>(v));
		_length++;
	}
	void remove(int idx) {
		int itemIdx = indices[idx];
		
		items[itemIdx] = move(items[items.size() - 1]);
		items.pop_back();
		indices.erase(indices.begin() + idx);
		
		if (itemIdx < _length - 1) {
			if (_lastIdx > -1) {
				indices[_lastIdx] = itemIdx;
				_lastIdx = -1;
			}
			else {
				auto it = find(indices.begin(), indices.end(), _length - 1);
				*it = itemIdx;
			}
		}
		_length--;
	}
	Item* get(int idx) {
		return items[indices[idx]].get();
	}
};


class ItemList6 {
private:
	int _length;
	node* p;
public:
	ItemList6() : _length(0), p(nullptr) {
	}
	int length() const {
		return _length;
	}
	void insert(int idx) {
		p = bts_insert(p, idx);
		_length++;
	}
	void remove(int idx) {
		p = bts_remove(p, idx);
		_length--;
	}
	node* get(int idx) {
		auto h = p;
		while (true) {
			if (h->key > idx) {
				h = h->left;
			}
			else if (h->key < idx) {
				h = h->right;
			}
			else {
				break;
			}
		}
		return h;
	}
};


class ItemList7 {
private:
	int _length;
	map<int, int> sl;
public:
	ItemList7() : _length(0) {
	}
	int length() const {
		return _length;
	}
	void insert(int idx) {
		sl[idx] = idx;
		_length++;
	}
	void remove(int idx) {
		sl.erase(idx);
		_length--;
	}
	auto get(int idx) {
		return sl.find(idx);
	}
};

int main() {
	/*
	ItemList4 i4;

	i4.insert(1, 0);
	i4.insert(2, 1);
	i4.insert(3, 2);
	i4.insert(4, 3);
	i4.insert(5, 4);
	i4.insert(6, 5);
	i4.insert(7, 6);
	i4.insert(8, 7);
	i4.insert(9, 8);
	i4.print();

	i4.remove(3);
	i4.print();
	i4.remove(0);
	i4.print();
*/
	int num = 20000;
	int avg = 2 * sqrt(num);
	int step = avg / 10;

	
	/*
	cout << "#######" << num << " " << avg << " " << step << endl;
	for (int j = 0; j < 10; j++) {
		ItemList1 i1;
		for (int i = 0; i < num; i++) {
			if (i >= avg) {
				i1.insert(i, avg / 2);
				i1.remove(avg / 2);
				Item* it1 = i1.get(0);
				Item* it2 = i1.get(step);
				Item* it3 = i1.get(2 * step);
				Item* it4 = i1.get(3 * step);
				Item* it5 = i1.get(4 * step);
				Item* it6 = i1.get(5 * step);
				Item* it7 = i1.get(6 * step);
				Item* it8 = i1.get(7 * step);
				Item* it9 = i1.get(8 * step);
				Item* it10 = i1.get(9 * step);
			}
			else {
				i1.insert(i, i / 2);
			}
		}
	}

	cout << "####### " << endl;
	for (int j = 0; j < 10; j++) {
		ItemList2 i2;
		for (int i = 0; i < num; i++) {
			int delKey;
			if (i % 2 == 0) {
				i2.insert(i, i / 2);
				delKey = (i - avg) / 2;
			}
			else {
				i2.insert(i, num - i / 2);
				delKey = num - (i - avg) / 2;
			}
			if (i >= avg) {
				i2.remove(delKey);
				Item* it1 = i2.get(0);
				Item* it2 = i2.get(step);
				Item* it3 = i2.get(2 * step);
				Item* it4 = i2.get(3 * step);
				Item* it5 = i2.get(4 * step);
				Item* it6 = i2.get(5 * step);
				Item* it7 = i2.get(6 * step);
				Item* it8 = i2.get(7 * step);
				Item* it9 = i2.get(8 * step);
				Item* it10 = i2.get(9 * step);
			}
		}
	}

	cout << "####### " << endl;
	for (int j = 0; j < 10; j++) {
		ItemList3 i3;
		for (int i = 0; i < num; i++) {
			int delKey;
			if (i % 2 == 0) {
				i3.insert(i, i / 2);
				delKey = (i - avg) / 2;
			}
			else {
				i3.insert(i, num - i / 2);
				delKey = num - (i - avg) / 2;
			}
			if (i >= avg) {
				i3.remove(delKey);
				Item* it1 = i3.get(0);
				Item* it2 = i3.get(step);
				Item* it3 = i3.get(2 * step);
				Item* it4 = i3.get(3 * step);
				Item* it5 = i3.get(4 * step);
				Item* it6 = i3.get(5 * step);
				Item* it7 = i3.get(6 * step);
				Item* it8 = i3.get(7 * step);
				Item* it9 = i3.get(8 * step);
				Item* it10 = i3.get(9 * step);
			}
		}
	}*/
	/*
	cout << "####### " << endl;
	for (int j = 0; j < 100; j++) {
		ItemList4 i4;
		for (int i = 0; i < num; i++) {
			
			if (i >= avg) {
				i4.insert(i, avg / 2);
				i4.remove(avg / 2);
				Item* it1 = i4.get(0);
				Item* it2 = i4.get(step);
				Item* it3 = i4.get(2 * step);
				Item* it4 = i4.get(3 * step);
				Item* it5 = i4.get(4 * step);
				Item* it6 = i4.get(5 * step);
				Item* it7 = i4.get(6 * step);
			    Item* it8 = i4.get(7 * step);
				Item* it9 = i4.get(8 * step);
				Item* it10 = i4.get(9 * step);
			}
			else {
				i4.insert(i, i / 2);
			}
		}
	}

	cout << "####### " << endl;

	for (int j = 0; j < 100; j++) {
		ItemList5 i4;
		for (int i = 0; i < num; i++) {

			if (i >= avg) {
				i4.insert(i, avg / 2);
				i4.remove(avg / 2);
				Item* it1 = i4.get(0);
				Item* it2 = i4.get(step);
				Item* it3 = i4.get(2 * step);
				Item* it4 = i4.get(3 * step);
				Item* it5 = i4.get(4 * step);
				Item* it6 = i4.get(5 * step);
				Item* it7 = i4.get(6 * step);
				Item* it8 = i4.get(7 * step);
				Item* it9 = i4.get(8 * step);
				Item* it10 = i4.get(9 * step);
			}
			else {
				i4.insert(i, i / 2);
			}
		}
	}*/

	cout << "####### " << endl;

	for (int j = 0; j < 100; j++) {
		ItemList6 i4;
		for (int i = 0; i < num; i++) {

			if (i >= avg) {
				i4.insert(i);
				i4.remove(i-avg);
				node* it1 = i4.get(i - avg + 1);
				node* it2 = i4.get(i - avg + step);
				node* it3 = i4.get(i - avg + 2 * step);
				node* it4 = i4.get(i - avg + 3 * step);
				node* it5 = i4.get(i - avg + 4 * step);
				node* it6 = i4.get(i - avg + 5 * step);
				node* it7 = i4.get(i - avg + 6 * step);
				node* it8 = i4.get(i - avg + 7 * step);
				node* it9 = i4.get(i - avg + 8 * step);
				node* it10 = i4.get(i - avg + 9 * step);
			}
			else {
				i4.insert(i);
			}
		}
	}

	cout << "####### " << endl;

	for (int j = 0; j < 100; j++) {
		ItemList7 i4;
		for (int i = 0; i < num; i++) {

			if (i >= avg) {
				i4.insert(i);
				i4.remove(i - avg);
				auto it1 = i4.get(i - avg + 1);
				auto it2 = i4.get(i - avg + step);
				auto it3 = i4.get(i - avg + 2 * step);
				auto it4 = i4.get(i - avg + 3 * step);
				auto it5 = i4.get(i - avg + 4 * step);
				auto it6 = i4.get(i - avg + 5 * step);
				auto it7 = i4.get(i - avg + 6 * step);
				auto it8 = i4.get(i - avg + 7 * step);
				auto it9 = i4.get(i - avg + 8 * step);
				auto it10 = i4.get(i - avg + 9 * step);
			}
			else {
				i4.insert(i);
			}
		}
	}

	cout << "####### " << endl;

	/*
	cout << "#######" << endl;
	for (int i = 0; i < 20000; i++) {
		i1.insert(i, i / 2);
	}
	cout << "####### " << endl;
	for (int i = 0; i < 20000; i++) {
		if (i % 2 == 0) {
			i2.insert(i, i / 2);
		}
		else {
			i2.insert(i, 20000 - i / 2);
		}
		
	}
	cout << "####### " << endl;*/

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