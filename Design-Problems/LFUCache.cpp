/*----------------------------------------------------------------------
 Design and implement LFU Cache

 Supported Operations:
 get(key) - Get the value (will always be positive) of the key if the key
            exists in the cache, otherwise return -1.
 put(key, value) - Set or insert the value if the key is not already present.
  	 	 When the cache reaches its capacity, it should invalidate the
 	 	 least frequently used item before inserting a new item.
 	 	 For the purpose of this problem, when there is a tie
 	 	 (i.e., two or more keys that have the same frequency),
 	 	 the least recently used key would be evicted.

 Idea : data structures used : Two doubly linked list, unordered_map.

 m_freqList: head -> F1 -> F3 -> F4  : Nodes in this list indicates Frequency.

 Each node in m_freqList also points to another list 'm_values' with (key,value) nodes.

 F1 : head --> N2 -> N3
 F3 : head --> N4
 F4 : head --> N5

 Here, N2 and N3 are (key-value) nodes with frequency = 1
 	   N4 with frequency = 3
 	   N5 with frequency = 4

 At any time, first node(N2) in first freqList will be least frequently and recently used node.
 time complexity is O(1).

 reference : Leetcode.com Problem # 460
----------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <utility>

using std::cout;
using std::vector;
using std::list;
using std::unordered_map;
using std::pair;

const int KEY_NOT_FOUND = -1;
class LFUCache
{
public:
	struct LRUNode
	{
		size_t m_freq;
		list< pair<int,int> > m_values;
		LRUNode(int frequency = 0) : m_freq(frequency)
		{}
	};

	// custom types
	using iptr = list<LRUNode>::iterator;
	using jptr = list< pair<int,int> >::iterator;

	LFUCache( size_t cap) : m_capacity(cap)
	{}

	int get(int key)
	{
		auto findKey = m_map.find(key);
		if( findKey != m_map.end())
		{
			// update frequency and store new iptr-jptr in m_map
			m_map[key] = updateFrequency(key, false);
			return m_map[key].second->second;
		}
		else
		{
			return KEY_NOT_FOUND;
		}
	}

	void put(int key, int value)
	{
		auto findKey = m_map.find(key);
		if( findKey != m_map.end())
		{
			// Key exists in the map. updateFrequency and return
			m_map[key] = updateFrequency(key, true, value);
			return;
		}
		else
		{
			// Key does not exist, check to see if capacity is reached
			if(m_map.size() == m_capacity)
			{
				evict();
			}
			m_map[key] = insert(key, value);
		}
	}

private:

	/* default argument for value indicates, if we are inserting a new node in m_freqList OR
	   just promoting an existing node */
	pair<iptr,jptr> updateFrequency(int key, bool updateVal, int value = -1)
	{
		iptr i = m_map[key].first;
		jptr j = m_map[key].second;

		/* nextI = iterator to next node in m_freqList where we want to promote this node
		 * save value and calculate new frequency
		 */
		iptr nextI = next(i);
		int newValue = j->second;
		if( updateVal )
		{
			newValue = value;
		}
		size_t freq = i->m_freq + 1;

		// Erase 'j' first and then 'i' if it becomes empty list
		i->m_values.erase(j);
		if(i->m_values.empty())
		{
			m_freqList.erase(i);
		}

		/* Calculate new i by inserting/reusing node with new freq
		 * Calculate j by inserting a new node at i's end.
		 */
		if( nextI == m_freqList.end() || nextI->m_freq != freq )
		{
			i = m_freqList.insert( nextI, LRUNode(freq));
		}
		else
		{
			i = nextI;
		}

		j = i->m_values.insert( i->m_values.end(), pair<int,int>(key, newValue));

		return {i,j};
	}

	// Evict least frequently used node
	void evict()
	{
		// we first need to get i and j and then we can find the key to be removed from m_map
		iptr i = m_freqList.begin();
		jptr j = i->m_values.begin();

		// erase entry in m_map using key, and erase j and i
		m_map.erase(j->first);
		i->m_values.erase(j);
		if( i->m_values.empty() )
		{
			m_freqList.erase(i);
		}
	}

	pair<iptr,jptr> insert(int key, int value)
	{
		// new key will have freq = 1, as it was not accessed before
		iptr i = m_freqList.begin();
		if( i == m_freqList.end() || i->m_freq != 1)
		{
			i = m_freqList.insert(i, LRUNode(1));
		}

		jptr j = i->m_values.insert( i->m_values.end(), pair<int,int>(key, value));
		return {i,j};
	}

	size_t m_capacity;
	list<LRUNode> m_freqList;
	unordered_map<int, pair<iptr,jptr>> m_map;


};

int main() {

	cout << " Testing LFU Cache" << std::endl;
	LFUCache cache(2);

	cache.put(1, 1);
	cache.put(2, 2);
	cout << cache.get(1) << std::endl;        // returns 1
	cache.put(3, 3);    					  // evicts key 2
	cout << cache.get(2) << std::endl;;       // returns -1 (not found)
	cout << cache.get(3) << std::endl;;       // returns 3.
	cache.put(4, 4);    					  // evicts key 1.
	cout << cache.get(1) << std::endl;;       // returns -1 (not found)
	cout << cache.get(3) << std::endl;;       // returns 3
	cout << cache.get(4) << std::endl;;       // returns 4
	return 0;
}
