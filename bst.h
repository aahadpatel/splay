#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <iomanip>
#include <algorithm>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the clear() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO 
		bool isBalanced(); //TODO 
		bool isBalanced_recursive(Node<Key, Value>* node); //added helper
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void clear_recursive(Node<Key, Value>* node); //added helper
		void print() const;
		Node<Key, Value>* getRoot();

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{ 
	// TODO
	mRoot = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	// TODO
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	// TODO
	if(mRoot != nullptr) return mRoot->getHeight();
	return 0;
}


/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced_recursive(Node<Key, Value>* node)
{
	// TODO
	//always true if root is NULL
	// if(node == NULL) return 1;
	int lh, rh;
	
	//CHECK LEFT AND RIGHT 
	//root
	if(node == nullptr) return true;
	if(node->getRight() != nullptr) rh = node->getRight()->getHeight();
	else rh = 0;
	//right height and left height
	bool left_balanced = isBalanced_recursive(node->getLeft());
	bool right_balanced = isBalanced_recursive(node->getRight());
	if(left_balanced == false) return false;
	if(right_balanced == false) return false;

	//if node left is not NULL
	if(node->getLeft() != nullptr) lh = node->getLeft()->getHeight();
	else lh = 0;
	if(lh - rh < 2 && lh-rh > -2) return true;
	else return false;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	return isBalanced_recursive(mRoot);
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{	
	// TODO
	if(mRoot == nullptr)
	{
		//creating a new node with initalized values 
		Node<Key, Value> *new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
		//initialize right, left, and parent to NULL
		//make sure to set hte height to 1
		new_node->setRight(nullptr);
		new_node->setLeft(nullptr);
		//root
		new_node->setHeight(1);
		new_node->setParent(nullptr);
		mRoot = new_node;
		//end
		return;
	}
	else if(mRoot != nullptr)
	{
		//set curr to Root 
		Node<Key, Value>* curr = mRoot;
		//setting new node
		Node<Key, Value> *new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
		//until curr's key does not equal the key 
		while(curr->getKey() != keyValuePair.first)
		{
	 		if(keyValuePair.first < curr->getKey())
	 		{
	 			//if left is valid, move down left 
	 			if(!curr->getLeft()) 
	 			{
	 				//setting height if not valid 
	 				new_node->setHeight(1);

	 				//set left as new node
	 				curr->setLeft(new_node);
	 				new_node->setParent(curr);
	 				//the new node's left and right will now be NULL
	 				new_node->setLeft(nullptr);
	 				new_node->setRight(nullptr);
	 				break;
	 			}
	 			else curr = curr->getLeft();

	 		}
	 		//second comparison get right 
	 		else if(keyValuePair.first > curr->getKey())
	 		{
	 			if(!curr->getRight())
	 			{
	 				//if not valid, set nodes
	 				curr->setRight(new_node);

	 				//height always becomes NULL
	 				new_node->setHeight(1);
	 				new_node->setParent(curr);

	 				//make sure to set lefts and rights to NULL
	 				new_node->setLeft(nullptr);
	 				new_node->setRight(nullptr);
	 				break;
	 				//set parent to curr
	 			}
	 			else curr = curr->getRight();
	 		}
		}
	}
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	//internal find store into curr
	Node<Key, Value>* curr = internalFind(key);
	//set prev and child as null
	Node<Key, Value>* prev = nullptr;
	Node<Key, Value>* child = nullptr;
	if(curr->getLeft() == nullptr && curr->getRight() == nullptr) {
		//curr only node case 
		if(curr->getParent() == nullptr) 
			{
				delete curr;
				mRoot = nullptr;
			}
		else
		{
			prev = curr->getParent();
			if(curr == prev->getLeft()) prev->setLeft(nullptr);
			else prev->setRight(nullptr);
			delete curr;
		}
		while(prev != nullptr) {
			if(prev->getLeft() == nullptr && prev->getRight() == nullptr) prev->setHeight(prev->getHeight()-1);
			else if(prev->getLeft() == nullptr) prev->setHeight(prev->getRight()->getHeight() + 1);
			else if(prev->getRight() == nullptr) prev->setHeight(prev->getLeft()->getHeight() + 1);
			else prev->setHeight(std::max(prev->getRight()->getHeight(), prev->getLeft()->getHeight()) + 1);
			prev = prev->getParent();
		}
	}
	else if(curr->getRight() == nullptr && curr->getLeft() != nullptr) {
		if(curr->getParent() == nullptr) 
		{
			Node<Key, Value>* temp = curr->getLeft();
			delete curr;
			mRoot = temp;
			temp->setParent(nullptr);
		}
		else
		{
			prev = curr->getParent();
			child = curr->getLeft();
			if(curr == prev->getLeft()) {
				prev->setLeft(child);
				child->setParent(prev);
			}
			else {
				prev->setRight(child);
				child->setParent(prev);
			}
			delete curr;
		}
		while(prev != nullptr) {
			if(prev->getLeft() == nullptr && prev->getRight() == nullptr) prev->setHeight(prev->getHeight()-1);
			else if(prev->getLeft() == nullptr) prev->setHeight(prev->getRight()->getHeight() + 1);
			else if(prev->getRight() == nullptr) prev->setHeight(prev->getLeft()->getHeight() + 1);
			else prev->setHeight(std::max(prev->getRight()->getHeight(), prev->getLeft()->getHeight()) + 1);
			prev = prev->getParent();
		}
	}
	else if(curr->getRight() != nullptr && curr->getLeft() == nullptr) {
		if(curr->getParent() == nullptr) 
		{
			Node<Key, Value>* temp = curr->getRight();
			delete curr;
			mRoot = temp;
			temp->setParent(nullptr);
		}
		else
		{
			prev = curr->getParent();
			child = curr->getRight();
			if(curr == prev->getLeft()) {
				prev->setLeft(child);
				child->setParent(prev);
			}
			else {
				prev->setRight(child);
				child->setParent(prev);
			}
			delete curr;
		}
		while(prev != nullptr) {
			if(prev->getLeft() == nullptr && prev->getRight() == nullptr) prev->setHeight(prev->getHeight()-1);
			else if(prev->getLeft() == nullptr) prev->setHeight(prev->getRight()->getHeight() + 1);
			else if(prev->getRight() == nullptr) prev->setHeight(prev->getLeft()->getHeight() + 1);
			else prev->setHeight(std::max(prev->getRight()->getHeight(), prev->getLeft()->getHeight()) + 1);
			prev = prev->getParent();
		}
	}
	else {
		Node<Key, Value>* pred = curr->getLeft();
		if(pred->getRight() != nullptr) {
			while(pred->getRight() != nullptr) {
				pred = pred->getRight();
			}
			prev = pred->getParent();
			if(pred->getLeft() == nullptr) {
				pred->setRight(curr->getRight());
				pred->setLeft(curr->getLeft());
				pred->getParent()->setRight(nullptr);

				if(curr->getParent() !=  nullptr) {
					if(curr == curr->getParent()->getLeft()) curr->getParent()->setLeft(pred);
					else curr->getParent()->setRight(pred);
					pred->setParent(curr->getParent());
				}
				else {
					pred->setParent(nullptr);
					this->mRoot = pred;
				}

				curr->getLeft()->setParent(pred);
				curr->getRight()->setParent(pred);
				delete curr;
			}
			else {
				//added these two lines for the child
				pred->getLeft()->setParent(pred->getParent());
				pred->getParent()->setRight(pred->getLeft());

				pred->setRight(curr->getRight());
				pred->setLeft(curr->getLeft());

				if(curr->getParent() !=  nullptr) {
					if(curr == curr->getParent()->getLeft()) curr->getParent()->setLeft(pred);
					else curr->getParent()->setRight(pred);
					pred->setParent(curr->getParent());
				}
				else {
					pred->setParent(nullptr);
					this->mRoot = pred;
				}

				curr->getLeft()->setParent(pred);
				curr->getRight()->setParent(pred);
				delete curr;
			}
			while(prev != nullptr) {
				if(prev->getLeft() == nullptr && prev->getRight() == nullptr) prev->setHeight(prev->getHeight()-1);
				else if(prev->getLeft() == nullptr) prev->setHeight(prev->getRight()->getHeight() + 1);
				else if(prev->getRight() == nullptr) prev->setHeight(prev->getLeft()->getHeight() + 1);
				else prev->setHeight(std::max(prev->getRight()->getHeight(), prev->getLeft()->getHeight()) + 1);
				prev = prev->getParent();
			}
		}
		else {
			pred->setRight(curr->getRight());
			if(curr->getParent() !=  nullptr) {
				if(curr == curr->getParent()->getLeft()) curr->getParent()->setLeft(pred);
				else curr->getParent()->setRight(pred);
				pred->setParent(curr->getParent());
			}
			else {
				pred->setParent(nullptr);
				this->mRoot = pred;
			}
			curr->getRight()->setParent(pred);
			delete curr;

			while(pred != nullptr) {
				if(pred->getLeft() == nullptr && pred->getRight() == nullptr) pred->setHeight(pred->getHeight()-1);
				else if(pred->getLeft() == nullptr) pred->setHeight(pred->getRight()->getHeight() + 1);
				else if(pred->getRight() == nullptr) pred->setHeight(pred->getLeft()->getHeight() + 1);
				else pred->setHeight(std::max(pred->getRight()->getHeight(), pred->getLeft()->getHeight()) + 1);
				pred = pred->getParent();
			}
		}
	}
}

/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/

//easier to do vs. iterative 
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_recursive(Node<Key, Value>* node)
{
	if(node != NULL)
	{
		clear_recursive(node->getRight());
		clear_recursive(node->getLeft());
		delete node;
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	//call rescursive implementation
	clear_recursive(mRoot);
	mRoot = nullptr;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	Node<Key, Value>* temp = mRoot;
	if(mRoot != NULL)
	{
		while(temp->getLeft() != NULL)
		{
			temp = temp->getLeft();
		} 
	}
	return temp;
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	// TODO
	Node<Key, Value>* current_node = mRoot;
	//at current 
	while(current_node)
	{
		if(key > current_node->getKey()) current_node = current_node->getRight();
		else if(key < current_node->getKey()) current_node = current_node->getLeft();
		//if equal
		else return current_node;
	}
	return nullptr;
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}


template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getRoot()
{
	return mRoot;
}


/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
