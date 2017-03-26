/*-----------------------------------------------------------------------------
 Repeated DNA Sequences

 All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
 Example: "ACGAATTCCG"

 When studying DNA, it is sometimes useful to identify repeated sequences within
 the DNA.

 Write a function to find all the 10-letter-long sequences (substrings) that
 occur more than once in a DNA molecule.

 Idea : This problem is just like any other substring problem that can be solved
        using "rolling Hash method". But here we calculate rolling hash differently.

        We take advantage of last byte being unique in ASCII value of A,C,G and T.
        And we are only looking for substring of length 10.

 reference : Leetcode.com Problem # 187
------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::cout;
using std::vector;
using std::string;
using std::unordered_map;

class Solution {
public:
   vector<string> findRepeatedDnaSequences(string s)
   {
      /* input string only contains A (0x41), C(0x43), G(0x47) and T(0x54)
       * Last byte of ASCII value of these characters is unique (1,3,7,4).
       * We can only use last 3 bits to capture it uniquely and calculate
       * and 10 characters. Hash value using 10*3 = 30 (less than 32 bits) bits
       * can be saved using a single integer.
       */

      unordered_map<int, bool> table;
      int i=0;
      vector<string> result;

      if(s.size() == 0) return result;
      int hashValue = 0;

      // calculate first Hash value using first 10 characters. Only consider first 30 bits.
      while( i < 10 )
      {
          hashValue = ((hashValue << 3) & 0x3FFFFFFF) | (s[i] & 7);
          ++i;
      }
      table[hashValue] = true;

      while( i < s.size() )
      {
         /* Calculate new Hash value with every new characters as we scan.
          * Check to see if its there in table, if it is then also look for bool
          * flag. If flag is set that means we found a new repeated sequence, if
          * its not then this is a duplicate sequence that we already covered,
          * so ignore it.
          */
          hashValue = ( (hashValue << 3) & 0x3FFFFFFF ) | ( s[i] & 7 );
          if( table.find(hashValue) != table.end() )
          {
              if( table[hashValue] )
              {
                  result.push_back(s.substr(i-9, 10));
                  table[hashValue] = false;
              }
          }
          else
          {
              table[hashValue] = true;
          }
          ++i;
       }

       return result;
    }
};

int main()
{
   Solution sol;
   string input = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
   vector<string> result = sol.findRepeatedDnaSequences( input );

   for( auto s : result )
   {
      cout << s << std::endl;
   }

   return 0;
}
