/*-----------------------------------------------------------------------------
 Word Ladder

 Given two words (beginWord and endWord), and a dictionary's word list, find all
 shortest transformation sequence(s) from beginWord to endWord, such that:

 Only one letter can be changed at a time
 Each transformed word must exist in the word list. Note that beginWord is not
 a transformed word. For example,

 Given:
 beginWord = "hit"
 endWord = "cog"
 wordList = ["hot","dot","dog","lot","log","cog"]

 Return:
 [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
 ]

 Idea: Here we will use Double ended BFS. Using BFS we will generate a graph and
       using graph we will build ladder.

       Generating correct graph is the key. Below we have used 'reverse' to help
       with direction of the graph. It also helps to ensure that there is no loop in
       the graph. One iteration we process front size (starting from 'Hit') and next
       iteration we process back side (starting from 'cog'), and we also toggle 'reverse'.

       1st iteration : forward = hit,      backward = cog
       2nd iteration : forward = cog,      backward = hot
       3rd iteration : forward = hot       backward = dog, log
       4th iteration : forward = dog, log  backward = dot, lot

 reference : Leetcode.com Problem # 126
------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <string>
#include <unordered_set>

using std::cout;
using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;

class Solution {
private:

   /* This function does BFS and generates the Graph. If ladder is not present then
    * it will return false.
    *
    */
    bool generateBFSGraph(unordered_set<string>& forward,
                          unordered_set<string>& backward,
                          unordered_set<string>& dict,
                          unordered_map<string, vector<string>>& graph,
                          bool reverse)
    {
       reverse = !reverse;
       // Ladder is not present. Return false.
       if(forward.empty()) return false;

       // Always process smaller set
       if(forward.size() > backward.size())
       {
          return generateBFSGraph( backward, forward, dict, graph, reverse );
       }

       // Erase 'forward' an d'backward' strings from dict to mark it as visited
       for( auto s : forward) dict.erase(s);
       for( auto s : backward) dict.erase(s);

       // Create new 'set' to add neighbors of 'forward'
       unordered_set<string> nextSet;
       bool done = false;
       for( auto word : forward )
       {
          string current = word;
          for(uint i=0; i<word.size(); ++i)
          {
             // Save current letter
             char letter = word[i];
             for(int j=0; j<26; ++j)
             {
                if( letter == 'a'+j) continue;

                word[i] = 'a'+j;

                // Check to see if 'word' is in the 'backward' set. If it is then we terminate.
                if( backward.find(word) != backward.end() )
                {
                   done = true;
                   reverse ? graph[word].push_back(current) : graph[current].push_back(word);
                }

                // Check dict and if it contains 'word' add it to nextSet. We will visit them in next call.
                if( dict.find(word) != dict.end() )
                {
                   nextSet.insert(word);
                   reverse ? graph[word].push_back(current) : graph[current].push_back(word);
                }
             }
             word[i] = letter;
          }
       }

       if( done ) return true;

       return generateBFSGraph( backward, nextSet, dict, graph, reverse );
    }

    /* Recursive function to perform DFS on given graph. Terminate when start and end matches.     *
     */

    void dsfGraph(string& start, string& end, unordered_map<string, vector<string>>& graph,
                  vector<vector<string>>& result, vector<string>& singleLadder )
    {
       if( start == end )
       {
          result.push_back(singleLadder);
          return;
       }

       for( auto s: graph[start] )
       {
          singleLadder.push_back(s);
          dsfGraph( s, end, graph, result, singleLadder);
          singleLadder.pop_back();
       }
    }

    /* PrintGraph for debugging purpose.
     */

    void printGraph(unordered_map<string, vector<string>>& graph)
    {
       cout << "****** Printing Graph ******\n";
       for( auto s: graph)
       {
          cout << s.first << "-> ";
          for( auto item: s.second)
          {
             cout << item << " ";
          }
          cout << std::endl ;
       }
       cout << std::endl ;
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
    {
       unordered_set<string> dict(wordList.begin(), wordList.end());
       vector<vector<string>> result;

       if( beginWord == endWord )
       {
          result.push_back(vector<string>(1, beginWord));
          return result;
       }

       unordered_set<string> forward;
       unordered_set<string> backward;

       unordered_map<string, vector<string>> graph;

       forward.insert(beginWord);
       backward.insert(endWord);

       bool isLadderPresent = generateBFSGraph( forward, backward, dict, graph, true);

       /* If 'isLadderPresent' is set that means a valid ladder exists. So we perform DFS over
        * 'graph' to find all valid ladders.
        */

       printGraph(graph);

       if( isLadderPresent )
       {
          vector<string> ladder;
          ladder.push_back( beginWord );
          dsfGraph( beginWord, endWord, graph, result, ladder );
       }

       return result;
    }
};

int main()
{
   Solution sol;
   vector<string> wordList = {"hot","dot","dog","lot","log","cog"};

   vector<vector<string>> result = sol.findLadders("hit", "cog", wordList);

   for( auto row : result)
   {
      for( auto s : row )
      {
         cout << s << " ";
      }
      cout << std::endl;
   }
   return 0;
}
