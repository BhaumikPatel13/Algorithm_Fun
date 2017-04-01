/*----------------------------------------------------------------------
 Course Schedule

 There are a total of n courses you have to take, labeled from 0 to n - 1.

 Some courses may have prerequisites, for example to take course 0 you have
 to first take course 1, which is expressed as a pair: [0,1]

 Given the total number of courses and a list of prerequisite pairs, return
 the ordering of courses you should take to finish all courses.

 For example,
 input : 4, [[1,0],[2,0],[3,1],[3,2]]
 output : [0,1,2,3] OR [0,2,1,3]

 idea : Here the key is to build a directed graph first and count the "degree"
        for all nodes.  After that start from a node with "degree = 0", and keep
        visiting node and reducing degree once visited, until all nodes are
        visited. In-code comments below for more details.

 reference : Leetcode.com Problem # 210
----------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>

using std::vector;
using std::cout;
using std::unordered_map;
using std::unordered_set;
using std::pair;
using std::queue;

class Solution
{
private:
   /* Graph would be a vector with size = "numCourses" where each element be an unorderd_set
    * to indicate that there exists a directed edge from index "i" node to all elements in
    * corresponding set. So once at node "i", we can also reach all the nodes in graph[i].
    */
   vector< unordered_set<int> > generateGRaph( int numCourses,
                                               vector<pair<int, int>>&  prerequisites)
   {
      vector< unordered_set<int> > graph( numCourses );

      for( auto item : prerequisites )
      {
         graph[item.second].insert( item.first );
      }

      return graph;
   }

   vector<int> calculateDegree( vector< unordered_set<int> >& graph )
   {
      vector<int> degree( graph.size(), 0);

      for( auto item: graph )
      {
         for( auto node : item )
         {
            degree[node]++;
         }
      }

      return degree;
   }

public:

   vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites)
   {
      /* First we want to generate the directed graph from input.
       */
      vector< unordered_set<int> > graph = generateGRaph( numCourses, prerequisites);

      /* Calculate the degree for each node. "Degree" is a count that indicates number of incoming
       * edges to this node.
       */
      vector<int> degree = calculateDegree( graph );
      vector<int>  result;

      /* Find nodes with degree 0, that will be our staring point in topological sort. There could
       * be multiple nodes with degree 0, this indicate many courses doesn't have any prerequisites.
       */
      queue<int> zeroQueue;
      for( int i=0; i< numCourses; ++i )
      {
         if( !degree[i] )
         {
            zeroQueue.push(i);
         }
      }

      /* Visit over all the nodes in graph starting from nodes in zeroQueue. Every iteration we
       * will pop one node from queue.
       */
      for( int i=0; i< numCourses; ++i )
      {
         /* If queue is empty that means we have a cycle in the graph, thus topological sort
          * is not possible. Return empty vector in this case. Else remove node from queue and
          * add it in result.
          */
         if( zeroQueue.empty() ) return {};
         int firstNode = zeroQueue.front();
         zeroQueue.pop();
         result.push_back(firstNode);

         /* Reduce degree of all the nodes that are reachable from firstNode. If degree of a node
          * becomes 0 then add it in queue.
          */
         for( auto node : graph[firstNode] )
         {
            --degree[node];
            if( !degree[node] )
            {
               zeroQueue.push(node);
            }
         }
      }

      return result;
   }
};

int main()
{
   vector<pair<int,int>> input1;
   input1.push_back(pair<int,int>(1,0));
   input1.push_back(pair<int,int>(2,0));
   input1.push_back(pair<int,int>(3,1));
   input1.push_back(pair<int,int>(3,2));

   Solution sol;
   vector<int> result = sol.findOrder(4, input1);
   for( auto i : result )
   {
      cout << i << " ";
   }

   vector<pair<int,int>> input2 = {pair<int,int>(1,2), pair<int,int>(3,4), pair<int,int>(0,3),
                                   pair<int,int>(0,1)};
   result = sol.findOrder(5, input2);
   cout << std::endl;
   for( auto i : result )
   {
      cout << i << " ";
   }

   return 0;

}
