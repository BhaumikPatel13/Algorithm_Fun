/*----------------------------------------------------------------------
 Design and implement LRU Cache

 It should support the following operations: get and put.

 get(key) - Get the value (will always be positive) of the key if the key exists
            in the cache, otherwise return -1.
 put(key, value) - Set or insert the value if the key is not already present.
                   When the cache reached its capacity, it should invalidate the
                   least recently used item before inserting a new item.

Idea : We will use two data structures : List and an unordered_map.
       "unordered_map" will have key-to-iterator mapping, if key exists then
       corresponding iterator will point to a node in list.

       List :   N1->N2->N3

       Key  : value
       ------------
        k1  : itn2   (itn2: iterator pointing to N2 in above List)
        k2  : itn3
        k3  : itn1

        At any time, first node (N1) will always represent recently used node,
        and last node (N3) always represent lease recently used node.


 reference : Leetcode.com Problem # 146
----------------------------------------------------------------------*/
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

using std::list;
using std::unordered_map;
using std::pair;
using std::cout;

class LRUCache
{
public:
  LRUCache(int cap):m_capacity(cap)
  {}

  int get(int key)
  {
    auto findKey = m_map.find(key);
    // Key not found
    if( findKey == m_map.end() )
    {
      return -1;
    }

    //Key found. Update List so this key moves to beginning of the list.
    m_list.splice(m_list.begin(), m_list, findKey->second);
    return m_list.begin()->second;
  }

  void set(int key, int value)
  {
    auto findKey = m_map.find(key);

    // If key exists
    if( findKey != m_map.end())
    {
      // move node to beginning of the list
      m_list.splice( m_list.begin(), m_list, findKey->second);
      // write new "value" to existing node
      m_list.begin()->second = value;
      return;
    }

    /* If key doesn't exist. Check to see if capacity is reached. If it is then
       evict en entry befoe adding new one */
    if( m_map.size() == m_capacity )
    {
     int deleteKey = m_list.back().first;
     m_list.pop_back();
     m_map.erase( deleteKey );
    }

    m_list.emplace_front( key, value );
    m_map[key] = m_list.begin();
  }

private:
  typedef list< pair<int,int> > pairList;
  typedef pairList::iterator pairListIt;

  size_t m_capacity;
  pairList m_list;
  unordered_map<int, pairListIt> m_map;
};

int main()
{
  LRUCache cache(2);
  cache.set(1,11);
  cache.set(2,22);
  cout << cache.get(2) << "\n";
  cache.set(2,200);
  cout << cache.get(2) << "\n";
  cache.set(3,33);
  cout << cache.get(1) << "\n";
  cout << cache.get(3) << "\n";
  return 0;
}
