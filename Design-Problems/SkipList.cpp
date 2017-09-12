/*
 * Implement Skip List data structure.
 * [ Reference : https://en.wikipedia.org/wiki/Skip_list ]
 */

#include <iostream>
#include <vector>

using namespace std;

class SkipListNode
{
public:
  int key;
  vector< SkipListNode* > next;

  SkipListNode( int k, int level ):key( k ),
                                   next( level+1, nullptr )
  {}
};

class SkipList
{
  int maxLevel;
  float prob;
  SkipListNode* head;
  int level;

  // private methods
  int generateRandomLevel();

public:

  SkipList( int maxL, float p );
  void insert( int newkey );
  void printSkipList();
  bool find( int key );
  void deleteKey( int key );
};

SkipList::SkipList( int maxL, float p ):maxLevel( maxL ),
                                        prob( p ),
                                        head( new SkipListNode( -1, maxL) ),
                                        level( 0 )
{}

int SkipList::generateRandomLevel()
{
  int currLevel = 0;
  float random = (float)rand()/RAND_MAX;
  while( random  < prob && currLevel < maxLevel )
  {
    currLevel++;
    random = (float)rand()/RAND_MAX;
  }
  return currLevel;
}


void SkipList::insert( int newkey )
{
  // Start from head and traverse list. Save all the level nodes in a vector.
  SkipListNode* current = head;
  vector<SkipListNode*> forwardInfo(maxLevel, nullptr );


  for(int i=level; i>=0; --i)
  {
    while( current->next[i] &&
           current->next[i]->key < newkey )
    {
      current = current->next[i];
    }
    forwardInfo[i] = current;
  }

  // current is pointing to previous node of a node which is equal or greater than key
  current = current->next[0];
  if( current == NULL || current->key != newkey )
  {
    int randomLevel = generateRandomLevel();

    // if this is the highest level generated so far then capture it into "level"
    if( level < randomLevel )
    {

      // Also update direction to fill in upper levels
      for(int i= level+1; i < maxLevel; ++i)
      {
        forwardInfo[i] = head;
      }
      level = randomLevel;
    }

    /* Create new node here and connect wires in both directions
       forwardInfo -------> nextNode
                      ^
                  insert Here
       "forwardInfo" is collection of all the previous nodes at different level
    */
    SkipListNode* slNode = new SkipListNode( newkey, randomLevel);
    for(int i=0; i<=randomLevel; ++i )
    {
      slNode->next[i] = forwardInfo[i]->next[i];
      forwardInfo[i]->next[i] = slNode;
    }
  }
}

bool SkipList::find( int key )
{
  SkipListNode* current = head;
  for( int i= level; i >=0; --i )
  {
    while( current->next[i] &&
           current->next[i]->key < key )
    {
      current = current->next[i];
    }
  }

  // we will reach previous node of a node which has high key value than key
  current = current->next[0];

  if( current && current->key == key )
  {
    return true;
  }
  return false;

}

/*  For delete, logic is same as insert. We build a forwardInfo vector and
 *  reach the node to be delete.
 */
void SkipList::deleteKey( int key )
{
  SkipListNode* current = head;
  vector<SkipListNode*> forwardInfo( maxLevel, nullptr );

  for( int i=level; i>=0; --i)
  {
    while( current->next[i] &&
           current->next[i]->key < key )
    {
      current = current->next[i];
    }
    forwardInfo[i] = current;
  }

  current = current->next[0];
  if( current && current->key == key )
  {
    for(int i=0; i<=level; ++i)
    {
      if( forwardInfo[i]->next[i] != current )
      {
        break;
      }
      forwardInfo[i]->next[i] = current->next[i];
    }
  }

  // what if this node was highest level node. In that case, clear levels
  while( level>0 && head->next[level] == nullptr )
  {
    --level;
  }
  delete current;

}

void SkipList::printSkipList()
{
  cout << " Skip List Info per Level " << endl;
  for( int i=0; i<= level; ++i )
  {
    cout << " Level " << i << ": ";
    SkipListNode* curr = head->next[i];

    while(curr)
    {
      cout << curr->key << " ";
      curr = curr->next[i];
    }
    cout << endl;
  }
}

int main()
{

  SkipList skpLst(4, 0.5);

  skpLst.insert(6);
  skpLst.insert(3);
  skpLst.insert(1);
  skpLst.insert(5);
  skpLst.insert(4);
  skpLst.insert(7);
  skpLst.insert(2);

  skpLst.printSkipList();

  cout << " Is 1 in the List? " << boolalpha << skpLst.find(1) << endl;
  cout << " Is 11 in the List? " << skpLst.find(11) << endl;

  skpLst.deleteKey(4);
  skpLst.deleteKey(1);

  skpLst.printSkipList();

  return 0;
}


