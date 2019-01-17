#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "rotateBST.h"

template <typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
public:
	SplayTree();
	void insert(const std::pair<const Key, Value>& keyValuePair);
	void remove(const Key& key);
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	typename SplayTree<Key, Value>::iterator findMin();
	typename SplayTree<Key, Value>::iterator findMax();
	void deleteMinLeaf();
	void deleteMaxLeaf();
protected:
	void splay(Node<Key, Value> *r);
};

template <typename Key, typename Value>
SplayTree<Key, Value>::SplayTree()
{

}

template <typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	//insert node into the tree using bst insert
	BinarySearchTree<Key, Value>::insert(keyValuePair);
	//node of corresponding key 
	Node<Key, Value>* curr = BinarySearchTree<Key, Value>::internalFind(keyValuePair.first);
	//if curr is not null splay
	if(curr != nullptr) splay(curr);
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
	//SplayTree<Key, Value>::iterator it = find(key);
	Node<Key, Value>* curr = BinarySearchTree<Key, Value>::internalFind(key);
	splay(curr);
	Node<Key, Value>* pred = curr->getLeft();
	Node<Key, Value>* right = curr->getRight();
	if(pred != nullptr)
	{
		if(pred->getRight() != nullptr) {
			while(pred->getRight() != nullptr) {
				pred = pred->getRight();
			}
		}
	}
	if(curr != nullptr) BinarySearchTree<Key, Value>::remove(key);
	else return;
	if(pred != nullptr) {
		splay(pred);
		this->mRoot = pred;
		pred->setRight(right);
	}
	else if(right != nullptr) {
		this->mRoot = right;
	}
	//if parent exists 
	else this->mRoot = nullptr;
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key)
{
	Node<Key, Value>* curr = this->mRoot;
	//not nullptr
	while((curr->getRight() != nullptr || curr->getLeft() != nullptr) && key != curr->getItem().first)
	{
		//go left
		if(key < curr->getItem().first)
		{
			if(curr->getLeft()) curr = curr->getLeft();
			else break;
		}
		//go right
		else if(key > curr->getItem().first)
		{
			if(curr->getRight()) curr = curr->getRight();
			else break;
		}
	}
	//splay function
	if(key != curr->getItem().first)
	{
		splay(curr);
		return typename SplayTree<Key, Value>::iterator(nullptr);
	}
	else
	{
		splay(curr);
		return typename SplayTree<Key, Value>::iterator(curr);
	}
}

//finding minimum, use getSmallestNode from bst
template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin()
{
	Node<Key, Value>* curr = BinarySearchTree<Key, Value>::getSmallestNode();
	splay(curr);
	return typename SplayTree<Key, Value>::iterator(curr);
}

//keep going right until you hit largest node
template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax()
{
	Node<Key, Value>* curr = this->mRoot;

	while(curr->getRight())
		curr = curr->getRight();
	splay(curr);
	return typename SplayTree<Key, Value>::iterator(curr);
}

//delete the minimum leaf 
template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf()
{
	Node<Key, Value>* curr = this->mRoot;

	if(curr->getLeft() == nullptr && curr->getRight() == nullptr)
	{
		delete curr;
		this->mRoot == nullptr;
		return;
	}
	//go left until nullptr and then go right  
	while(curr->getLeft() != nullptr || curr->getRight() != nullptr)
	{
		if(curr->getLeft() != nullptr)
		{
			curr = curr->getLeft();
		}
		else
		{
			curr = curr->getRight();
		}
	}

	//set pointer equal to the temp parent 
	Node<Key, Value>* temp_parent = curr->getParent();
	if(curr->getParent()->getRight() == curr)
	{
		delete curr->getParent()->getRight();
		temp_parent->setRight(nullptr);
	}
	else 
	{
		delete curr->getParent()->getLeft();
		temp_parent->setLeft(nullptr);
	}
	//REMEMBER TO SPLAY 
	splay(temp_parent);
}

//delete max leaf 
template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf()
{
	Node<Key, Value>* curr = this->mRoot;

	if(curr->getLeft() == nullptr && curr->getRight() == nullptr)
	{
		delete curr;
		this->mRoot == nullptr;
		return;
	}

	//go right until nullptr then go left
	while(curr->getLeft() != nullptr || curr->getRight() != nullptr)
	{
		if(curr->getRight() != nullptr)
		{
			curr = curr->getRight();
		}
		else
		{
			curr = curr->getLeft();
		}
	}

	//set pointer equal to the temp parent 
	Node<Key, Value>* temp_parent = curr->getParent();
	if(curr->getParent()->getRight() == curr)
	{
		delete curr->getParent()->getRight();
		temp_parent->setRight(nullptr);
	}
	else 
	{
		delete curr->getParent()->getLeft();
		temp_parent->setLeft(nullptr);
	}
	//REMEMBER TO SPLAY 
	splay(temp_parent);
}

//splay function
template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r)
{
	while(true)
	{
		if(r == nullptr) {
			break;
		}
		else if(r->getParent() == nullptr)
		{
			break;
		}
		else if(r->getParent()->getParent() == nullptr)
		{
			if(r->getParent()->getLeft() == r)
			{
				this->rightRotate(r);
			} 
			else {
				this->leftRotate(r);
			}
		}
		//if r has a parent and a grandparent 
		else if(r->getParent()->getParent() != nullptr && r->getParent() != nullptr)
		{
			//if r's parent's left child is r and r's grandparent's left child is r's parent
			if(r->getParent()->getLeft() == r && r->getParent()->getParent()->getLeft() == r->getParent())
			{
				this->rightRotate(r->getParent());
				this->rightRotate(r);
			}
			//if r's parent's right child is r and r's grandparent's rught child is r's parent
			else if(r->getParent()->getRight() == r && r->getParent()->getParent()->getRight() == r->getParent())
			{
				this->leftRotate(r->getParent());
				this->leftRotate(r);
			}
			//if r's parent's left child is r and r's grandparent's right child is r's parent
			else if(r->getParent()->getLeft() == r && r->getParent()->getParent()->getRight() == r->getParent())
			{
				this->rightRotate(r);
				this->leftRotate(r);
			}
			//if r's parent's right child is r and r's grandparent's left child is r's parent
			else if(r->getParent()->getRight() == r && r->getParent()->getParent()->getLeft() == r->getParent())
			{
				this->leftRotate(r);
				this->rightRotate(r);
			}
		}
	}
}

#endif