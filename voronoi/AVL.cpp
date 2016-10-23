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
#include "AVL.h"

using namespace std;
using namespace AVL;


template <class V, class T>
Node::Node(Node* p, T* v, V k) : left(nullptr), right(nullptr), parent(p), value(v), key(k) {}

template <class V, class T>
char Node::bfactor() const {
	return (right ? right->height : 0) - (left ? left->height : 0);
}

template <class V, class T>
void Node::updateHeight() {
	unsigned char hl = (left ? left->height : 0);
	unsigned char hr = (right ? right->height : 0);
	height = (hl > hr ? hl : hr) + 1;
}




template <class V, class T>
AVLTree::AVLTree() : head(nullptr) {}

template <class V, class T>
void AVLTree::rotateright() {
	auto q = move(head->left);
	head->left = move(q.right);
	head->left->parent = head.get();
	q->right = move(head);
	q->right->parent = q.get();
	head = move(q);
	q.parent = nullptr;
	head->updateHeight();
	head->right->updateHeigh();
}

template <class V, class T>
void AVLTree::rotateleft() {
	auto q = move(head->right);
	head->right = move(q.left);
	head->right->parent = head.get();
	q->left = move(head);
	q->left->parent = q.get();
	head = move(q);
	q.parent = nullptr;
	head->updateHeight();
	head->left->updateHeigh();
}

template <class V, class T>
void AVLTree::insert(const V key, const T* value) {
	if (!head) {
		head = make_unique<Node>(nullptr, value, key);
		return;
	}
	auto n = head.get();
	while (true) {
		if (n->key < key) {
			if (!n->right) {
				n->right = make_unique<Node>(n, value, key);
				break;
			}
			else {
				n = n->right.get();
			}
		}
		else {
			if (!n->left) {
				n->left = make_unique<Node>(n, value, key);
				break;
			}
			else {
				n = n->left.get();
			}
		}
	}
}

template <class V, class T>
void AVLTree::remove(const V key) {
	auto n = head.get();
	while (true) {
		if (n->key == key) {
			if (n->left && n->right) {
				if (n->left->height > n->right->height) {

				}
			}
			break;
		}
		else if (n->key < key) {
			n = n->right.get();
		}
		else {
			n = n->left.get();
		}
	}
}

template <class V, class T>
T* AVLTree::get(const V key) const {

}


