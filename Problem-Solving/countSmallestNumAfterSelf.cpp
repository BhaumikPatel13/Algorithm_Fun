/*----------------------------------------------------------------------
[1] Count of Smaller Numbers After Self

You are given an integer array nums and you have to return a new counts array.
The counts array has the property where counts[i] is the number of smaller
elements to the right of nums[i].

Example:

Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element

Return the array [2, 1, 1, 0].

Idea : This kind of problems where nums[i] > nums[j] ( where i<j ) is related to
      inversion numbers. And it can be easily solved by doing merge sort.
      Keep sorting the array and keep calculating the results. Inline comments
      included for more details.

reference : Leetcode.com Problem # 315
----------------------------------------------------------------------*/
#include<iostream>
#include<vector>
#include<utility>

using std::cout;
using std::vector;
using std::pair;
using std::make_pair;

class Solution
{
public:
  vector<int> result;

  // In parameters, "start" is first element and "end" is element after last
  void mergeSortAndCount( vector<pair<int,int>>& index, int start, int end )
  {
      // base case : single node or zero node
      if( (end-start) <= 1 ) return;

      // Merge sort logic
      int mid = (start + end)/2;
      mergeSortAndCount( index, start, mid );
      mergeSortAndCount( index, mid, end );

      /* Here we need to sort both parts and while sorting, update the count
         in final result */
      vector< pair<int,int> > sorted;
      int i = start;
      int j = mid;
      while( i< mid || j<end )
      {
        /* push smaller elemts into "sorted" vector one by one. If element being
        pushed is from first half (start-mid) then increse the "count" in result
        by (j-mid). This counts how many elemtns from second half went in "sorted"
        before current element */
        while( i<mid &&
               ( j >= end || index[i].first <= index[j].first))
        {
          sorted.push_back( index[i] );
          result[ index[i].second ] += (j- mid);
          ++i;
        }

        while( j<end &&
               ( i>= mid || index[i].first > index[j].first ))
        {
          sorted.push_back(index[j]);
          ++j;
        }
      }

      //copy "sorted" vector into original "index" vector from start-to-end
      for( int x=start; x < end; ++x)
      {
        index[x] = sorted[x - start];
      }
  }

  vector<int> countSmaller( vector<int>& nums )
  {
     /* Here we need a vector<pair> to keep track of actual nums element and
        its index. So after merge sort, if this element has been moved, we still
        can fill the answer at correct index in "result" vector */
    vector< pair<int,int> > index;
    for(int i=0; i<nums.size(); ++i)
    {
      index.push_back( make_pair(nums[i], i));
    }

    result.resize(nums.size(), 0);
    mergeSortAndCount( index, 0, nums.size());
    return result;
  }
};

int main()
{
  Solution sol;
  vector<int> input = {5,2,6,1};
  vector<int> output = sol.countSmaller(input);

  for( auto item : output)
  {
    cout << item << " ";
  }
  return 0;
}
