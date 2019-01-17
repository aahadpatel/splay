#ifndef CACHELRU_H
#define CACHELRU_H

#include <iostream>
#include "splayTree.h"
#include <stdexcept>
#include <cstdlib>

template <typename Key, typename Value>
class cacheLRU 
{
public:
	cacheLRU(int capacity);
	~cacheLRU();
	void put(const std::pair<const Key, Value>& keyValuePair);
	std::pair<const Key, Value> get(const Key& key);
//setting size, max_capacity, declaring splay tree 
private:
	int size;
	int max_capacity;
	SplayTree<Key, Value>* cache_splay;
};

//constructor
template <typename Key, typename Value>
cacheLRU<Key, Value>::cacheLRU(int capacity)
{
	cache_splay = new SplayTree<Key, Value>();
	//set max = capacity
	max_capacity = capacity;
	size = 0;
}

//destructor 
template <typename Key, typename Value>
cacheLRU<Key, Value>::~cacheLRU()
{
	delete cache_splay;
}

//put function
template <typename Key, typename Value>
void cacheLRU<Key, Value>::put(const std::pair<const Key, Value>& keyValuePair)
{
	if(size == max_capacity)
	{
		cache_splay->deleteMinLeaf();
		cache_splay->insert(keyValuePair);
	}
	//if less
	else
	{
		cache_splay->insert(keyValuePair);
		size++;
	}
}
//get 
template <typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key, Value>::get(const Key& key)
{
	typename SplayTree<Key, Value>::iterator find_cache(cache_splay->find(key));
	if(find_cache != cache_splay->end()) return *find_cache;
	else throw std::logic_error("Key is not found");
}

#endif
