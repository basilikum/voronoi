#pragma once
#include <iostream>
#include <memory>

using namespace std;

namespace AVL {

	template <class V, class T>
	struct Node {
		unique_ptr<Node> left;
		unique_ptr<Node> right;
		Node* parent;
		T* value;
		V key;
		int height;
	};

	template <class V, class T>
	class AVLTree {
	private:
		unique_ptr<Node> head;
	public:
		void insert(const V key, const T* value);
		void remove(const V key);
		T* get(const V key) const;
	};

	template <class V, class T>
	AVLTree::AVLTree() : head(nullptr) {}

	template <class V, class T>
	void AVLTree::insert(const V key, const T* value) {
		if (!head) {
			head = make_unique<Node>(nullptr, nullptr, nullptr, value, key);
			return;
		}
		auto n = head.get();
		while (true) {
			if (n->key < key) {
				if (!n->right) {
					n->right = make_unique<Node>(nullptr, nullptr, n, value, key);
					break;
				}
				else {
					n = n->right.get();
				}
			}
			else {
				if (!n->left) {
					n->left = make_unique<Node>(nullptr, nullptr, n, value, key);
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
}

