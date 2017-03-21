/*----------------------------------------------------------------------
 Median of Two Sorted Arrays

 There are two sorted arrays nums1 and nums2 of size m and n respectively.

 Find the median of the two sorted arrays. The overall run time complexity
 should be O(log (m+n)).

 Examples :
 [1] {1,3} {2} median = 2.0
 [2] {1,2} {3,4} median = (2+3)/2 = 2.5

 Idea : Main idea here is to use a binary search logic and trim our search
        space every iteration. Every iteration we will look for Kth element
        in sorted vector. Kth element is (k-1) indexed element in vector.

        Both num1 and num2 are sorted.

        nums1 : =======#.......
        nums2 : -------@///////

        # and @ are medians from num1 and num2.Two cases,
        [1] # < @ : median is between # and @. so ignore === and ///
        [2] @ < # : median is between @ and #. so ignore --- and ...
        [3] @ = # : median is same as @ and #.

        in [1] and [2], new chunk includes @ and # as well.

 reference : Leetcode.com Problem # 4
----------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;
using std::min;

class Solution
{
public:
   double findMedian( vector<int>& nums1, vector<int>& nums2 )
   {
      int size1 = nums1.size();
      int size2 = nums2.size();

      int total = size1 + size2;
      double result;

      if( total%2 == 0)
      {
         /* For even size vector, median will be average of (total/2) and (total/2)-1
          * index elements. So here we can pass 'k' by adding 1 to (total/2)-1 and
          * (total/2) index.
          */
         result = findKthElement( nums1, 0, size1, nums2, 0, size2, (total/2)) +
                  findKthElement( nums1, 0, size1, nums2, 0, size2, (total/2)+1);
         result /= 2.0;
      }
      else
      {
         /* For odd size vector, media will be "total/2" index. But findKthElement
          * will return (K-1) index element, here we want to pass (total/2)+1
          */
         result = findKthElement(nums1, 0, size1, nums2, 0, size2, (total/2)+1);
      }

      return result;
   }

   /* Parameters s1/s2 indicates start and e1/e2 indicates end of vector. e1/e2 are
    * beyond vector boundary. 'k' indicates kth element in mergeSorted num1 and num2
    * result.
    */
   int findKthElement( vector<int>& nums1, int s1, int e1,
                       vector<int>& nums2, int s2, int e2,
                       int k )
   {
      // swap if required to make nums1 always smaller
      if( e1-s1 > e2-s2 )
      {
         return findKthElement( nums2, s2, e2, nums1, s1, e1, k );
      }

      /* Base case termination conditions
       * [1] nums1 empty : find kth element in nums2
       * [2] k = 1 : find min (nums1[s1], nums2[s2])
       */
      if( s1 == e1 ) return nums2[s2+k-1];
      if( k == 1) return min( nums1[s1], nums2[s2] );

      /* Get medians of both vector and compare.
       * nums1 might be smaller than k/2.
       * Also len1 will never be 0, as we've already covered bases cases.
       */
      int len1 = min(k/2, e1-s1);
      int len2 = k - len1;

      if( nums1[s1+len1-1] < nums2[s2+len2-1] )
      {
         return findKthElement( nums1, s1+len1, e1, nums2, s2, s2+len2, k-len1 );
      }
      else if( nums1[s1+len1-1] > nums2[s2+len2-1] )
      {
         return findKthElement( nums1, s1, s1+len1, nums2, s2+len2, e2, k-len2 );
      }
      else
      {
         return nums1[s1+len1-1];
      }
   }

};

int main()
{
   vector<int> v1 = {1,2,3,4};
   vector<int> v2 = {5,6,7,8};
   Solution s1;
   cout << s1.findMedian(v1, v2) << std::endl;

   v1 = {1};
   v2 = {5,6,7,8,9,10};
   cout << s1.findMedian(v1, v2) << std::endl;

   v1 = {3,4,5,6};
   v2 = {};
   cout << s1.findMedian(v1, v2) << std::endl;

   return 0;
}
