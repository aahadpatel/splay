#ifndef ROTATE_BST_H
#define ROTATE_BST_H

#include "bst.h"

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
public:
	void transform(rotateBST& t2) const;
protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
};

template <typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST<Key, Value>& t2) const
{

}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r)
{
	//nullptr return
	if(r == nullptr) return;
	if(r->getParent() == nullptr) return;
	Node<Key, Value>* parent = r->getParent();
	Node<Key, Value>* grand = parent->getParent();
	//first case- grandparent is nullptr
	if(grand == nullptr) {
		parent->setParent(r);
		parent->setRight(r->getLeft());
		if(r->getLeft() != nullptr) r->getLeft()->setParent(parent);
		r->setParent(nullptr);
		r->setLeft(parent);
		this->mRoot = r;
	}
	//if grand is not nullptr 
	else {
		if(r == parent->getRight()) {
			if(parent->getParent()->getLeft() == parent)
				grand->setLeft(r);
			else grand->setRight(r);
			r->setParent(grand);
			parent->setRight(r->getLeft());
			if(r->getLeft() != nullptr) r->getLeft()->setParent(parent);
			parent->setParent(r);
			r->setLeft(parent);
			parent->setParent(r);
		}
	}
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r)
{
	//return if nullptr
	if(r == nullptr) return;
	if(r->getParent() == nullptr) return;
	//declare parent and grandparent 
	Node<Key, Value>* parent = r->getParent();
	Node<Key, Value>* grand = parent->getParent();
	if(grand == nullptr) {
		parent->setParent(r);
		parent->setLeft(r->getRight());
		if(r->getRight() != nullptr) r->getRight()->setParent(parent);
		r->setParent(nullptr);
		r->setRight(parent);	
		this->mRoot = r;
	}
	else {
		//if r is parent's left child
		if(r == parent->getLeft()) {
			if(parent->getParent()->getLeft() == parent)
				grand->setLeft(r);
			else grand->setRight(r);
			r->setParent(grand);
			parent->setLeft(r->getRight());
			if(r->getRight() != nullptr) r->getRight()->setParent(parent);
			parent->setParent(r);
			r->setRight(parent);
			parent->setParent(r);
		}
	}
}

#endif