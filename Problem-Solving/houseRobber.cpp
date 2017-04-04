/*----------------------------------------------------------------------
 House Robber III

 Thief is in the area where all houses form a binary tree. It will automatically
 contact the police if two directly-linked houses were broken into.

 Determine the maximum amount of money the thief can rob without alerting the police.

 Example 1:
    *3
    / \
   2   3
    \   \
    *3  *1
 Maximum amount of money the thief can rob = 3 + 3 + 1 = 7. (values with * in above tree)

 Idea : Thief cannot rob node and its children at the same time.
        So on a given node "root", we have two options.
        [1] Skip root node [2] Rob root node
        We can maintain a result with two values where both values
        indicate ( [1],[2] ).

                   ( skip_root , rob_root )
                        /            \
                       /              \
                      /                \
           (skip_left, rob_left) ( skip_right, rob_right)

        Diagram indicates that each node can have 2 profit values :

        [1] If we skip root then thief can rob both child nodes and profit will be,
        skip_root = maximum profit on left + maximum profit on right
                  = max( skip_left,rob_left) + max( skip_right, rob_right)


        [2] If we rob root, then thief would have to skip children.
        rob_root = root's value + skip left child + skip right child
                 = root->val + skip_left + skip_right

 reference : Leetcode.com Problem # 337
----------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;
using std::max;

struct TreeNode
{
   int val;
   TreeNode* left;
   TreeNode* right;

   TreeNode(int v ): val(v), left(nullptr), right(nullptr) {}
};


class Solution
{
private:

   /* Result vector contains two values,
    * result[0] = profit if we skip this node
    * result[1] = profit if we rob this node
    */
   vector<int> maximizeProfit( TreeNode* root )
   {
      /* If root is null then result set will be (0,0)
       */
      vector<int> result(2,0);
      if( root == nullptr )
      {
         return result;
      }

      /* Get result for left and right child recursively
       */
      vector<int> leftResult = maximizeProfit( root->left );
      vector<int> rightResult = maximizeProfit( root->right );

      // result[0] has profit value without considering root node
      result[0] = max( leftResult[0], leftResult[1]) +
                  max( rightResult[0], rightResult[1]);

      // for result[1], If we consider root node, we have to skip child nodes
      result[1] = root->val + leftResult[0] + rightResult[0];

      return result;
   }

public:
   int rob( TreeNode* root )
   {
      vector<int> result = maximizeProfit( root );
      /* return maximum profit that we get out of skipping/robbing nodes
       */
      return max( result[0], result[1] );
   }
};

int main()
{
   TreeNode* root  = new TreeNode(3);
   root->left = new TreeNode(2);
   root->right = new TreeNode(3);
   root->left->right = new TreeNode(3);
   root->right->right = new TreeNode(1);

   Solution sol;
   cout << " Tree1 Max Profit is :" << sol.rob( root ) << std::endl;

   /*
     3
    / \
   4   5
  / \   \
 1   3   1
    */

   TreeNode* root2  = new TreeNode(3);
   root2->left = new TreeNode(4);
   root2->right = new TreeNode(5);
   root2->left->left = new TreeNode(1);
   root2->left->right = new TreeNode(3);
   root2->right->right = new TreeNode(1);
   cout << "\n Tree2 Max Profit is :" << sol.rob( root2 ) << std::endl;

   return 0;
}
