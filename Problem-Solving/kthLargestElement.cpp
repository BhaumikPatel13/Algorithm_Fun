/*----------------------------------------------------------------------
 Kth Largest Element in an Array

 Find the kth largest element in an unsorted array. Note that it is the kth
 largest element in the sorted order, not the kth distinct element.

 For example,
 Given [3,2,1,5,6,4] and k = 2, return 5.

 Idea: If we use extra space then it would be a trivial solution. Here we
       will use a variation of quick sort, which will allow us not to any
       extra space to solve this.

       Kth largest element in unsorted array would be, "k-1" index (0 based indexing)
       element in a descending order sorted array.

       We can use quick sort partitioning to find an index for pivot and then
       split array into two part. Left and right to pivot.
                Left        Pivot        Right
                =============+**************
       [1] If k-1 is same as pivot index then we stop and return the element.
       [2] If k-1 is beyond pivot index, then we consider only right part and
           apply partitioning again until we find solution.
       [3] If k-1 is lower than pivot index, then we only consider left part.

 reference : Leetcode.com Problem # 215
----------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;
using std::swap;

class Solution {
private:
   /* Basic quick sort partitioning
    */
    int partition( vector<int>& nums, int left, int right)
    {
       int pivot = left;
       int l = left+1;
       int r = right;

       while( l <= r)
       {
          /* We are sorting array in descending order, thus elements
           * greater or equal to pivot goes on left side and elements
           * less or equal to pivot goes on right side.
           */
          if( nums[l] < nums[pivot] && nums[pivot] < nums[r])
          {
             swap(nums[l++], nums[r--]);
          }
          if( nums[l] >= nums[pivot]) l++;
          if( nums[r] <= nums[pivot] ) r--;
       }
       swap( nums[pivot], nums[r]);

       /* Index 'r' indicates the correct place for partition
        */
       return r;
    }

public:
    int findKthLargest(vector<int>& nums, int k)
    {
       int left = 0;
       int right = nums.size()-1;

       if( uint(k) > nums.size()) return -1;

       /* Loop will terminate when we find our element
        */
       while( true )
       {
          int pivotIndex = partition( nums, left, right);

          /* If index matches "k-1" then this is our Kth largest
           * element in the array.
           */
          if(k-1 == pivotIndex ) return nums[pivotIndex];

          /* Choose left or right side by re-adjusting 'left'/'right'
           * values.
           */
          if(k-1 > pivotIndex )
          {
             left = pivotIndex+1;
          }
          else
          {
             right = pivotIndex-1;
          }
       }
    }
};

int main()
{
   vector<int> input = {3,5,6,4,2,1};
   Solution sol;

   cout << " 4th Largest Element is : " << sol.findKthLargest(input,4) << std::endl;
   cout << " 2nd Largest Element is : " << sol.findKthLargest(input,2) << std::endl;

   return 0;
}
