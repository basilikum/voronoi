#pragma once
#include <iostream>
#include <memory>

using namespace std;

namespace AVL {

	template <class V, class T>
	class Node {
	public:
		Node(Node* p, T* v, V k);
		unique_ptr<Node> left;
		unique_ptr<Node> right;
		Node* parent;
		T* value;
		V key;
		unsigned char height;
		char bfactor() const;
		void updateHeight();
	};

	template <class V, class T>
	class AVLTree {
	private:
		unique_ptr<Node> head;
		
	public:
		AVLTree();
		void insert(const V key, const T* value);
		void remove(const V key);
		T* get(const V key) const;
	};
}

