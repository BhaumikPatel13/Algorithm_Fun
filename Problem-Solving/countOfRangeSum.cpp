/*----------------------------------------------------------------------
Count of Range Sum

Given an integer array nums, return the number of range sums that lie in
[lower, upper] inclusive. Range sum S(i, j) is defined as the sum of the elements
in nums between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 5, -1], lower = -2, upper = 2,
Return 3.
The three ranges are : [0, 0], [2, 2], [0, 2]
and their respective sums are: -2, -1, 2.

Idea : The main idea here is to calculate "sum" vector. It is intuitive to come
       up with "sum" vector, as we need various range of sums from input.
       So  sum "so far" can be used to find sum[j]-sum[i]for j>i; Going over all
       sum pairs will result in O(n^2).

       Instead we can use "Merge sort" on Sum vector, and count instaces that meets
       condition. After merge sort first and second half will be sorted.

reference : Leetcode.com Problem # 327
----------------------------------------------------------------------*/
#include<iostream>
#include<vector>

using std::vector;
using std::cout;

class Solution
{
public:
    int mergeSortAndCount( vector<long>& sum, int start, int end, int lower, int upper)
    {
      // base case : single or 0 element in "sum"
      if( (end-start) <= 1 ) return 0;

      // find "mid" and make recursive calculating
      int mid = (start + end)/2;
      int count = mergeSortAndCount( sum, start, mid, lower, upper ) +
                  mergeSortAndCount( sum, mid, end, lower, upper );

      /* Here we need to sort both half and while sorting count instances which
      satisfies condition: lower <= sum[j]-sum[i] <= upper */
      vector<long> sorted( end-start, 0);
      int low=mid, up=mid, j = mid;

      for(int i=start, s=0; i<mid; ++i, ++s)
      {
        /* Find lower bound and upper bound for sum difference and add it to count
        lower bound : index in second half where diff is not < lower anymore
        upper bound : index in second half where diff is not <= upper */
        while( low < end && sum[low]-sum[i] < lower ) low++;
        while( up < end && sum[up]-sum[i] <= upper ) up++;
        count += (up-low);

        while( j < end && sum[j]<sum[i])
        {
          sorted[s++] = sum[j++];
        }
        sorted[s] = sum[i];
      }

      //copy sorted into original sum
      for(int i=start; i<end; ++i)
      {
        sum[i] = sorted[i-start];
      }
      return count;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper)
    {
      if( nums.size() == 0 ) return 0;

      /* create "sum" vector, where each element represents sum so far without
      counting current element in "nums" */
      vector<long> sum( nums.size()+1, 0);
      for(int i=0; i<nums.size(); ++i)
      {
        sum[i+1] = sum[i] + nums[i];
      }

      // Process "sum" vector using merge sort.
      return mergeSortAndCount( sum, 0, sum.size(), lower, upper);
    }
};

int main()
{
  vector<int> input = {-2,5,-1};
  Solution sol;
  cout << sol.countRangeSum(input, -2, 2);
  return 0;
}
