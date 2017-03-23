/*----------------------------------------------------------------------
 Rolling Hash implementation using Rabin-Karp method

 Rolling hash can be used to search for a "pattern" in given "text" to
 achieve O(n) search complexity.

 Algorithm:
    + First  compute the Hash for "pattern".
    + Then keep computing Hash value for all the substring with same
      length as pattern from "text".
    + If Hash value matches then compare the string character by character
    +  If it matches then note the starting position and move on.

 Calculating Rolling Hash:
    + We can use existing hash value to calculate new hash value.
    Assuming, a=1, b=2, c=3, d=4, prime = 5 (some prime number)
    text = "abcd"

    Hash("abc") = 1*pow(prime, 0) + 2*pow(prime, 1) + 3*pow(prime, 2)
                = 86

    Hash("bcd") = (Hash("abc") - Hash("a") )/prime + Hash("d");
    Here Hash("abc") = 86;
         Hash("a")   = 1*pow(prime, 0) = 1;
         Hash("d")   = 4*pow(prime, 2) = 100;

----------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::cout;
using std::vector;
using std::string;
using std::pow;

static const int PRIME = 37;
class rabinKarpSearch
{
private:
   long createHash( string input, int len )
   {
      long hash = 0;
      for(int i=0; i<len; ++i)
      {
         hash += ( input[i] * pow( PRIME, i) );
      }
      return hash;
   }

   long reCalculateHash( long oldHash, string& text, int oldIndex, int newIndex, int pLen)
   {
      long newHash = oldHash - text[oldIndex];
      newHash /= PRIME;
      newHash += ( text[newIndex]* pow( PRIME, pLen-1));
      return newHash;
   }

public:
   vector<int> matchPattern( string pattern, string text)
   {
      int pLen = pattern.length();
      int tLen = text.length();
      vector<int> result;

      /* Calculate Hash for "pattern" and first substring from "text"
       * with length equal to pattern length.
       */
      long patternHash = createHash( pattern, pLen );
      long textHash = createHash( text, pLen );

      for(int i=0; i <= tLen-pLen; ++i)
      {
         /* If Hash matches and substring is also same then 'i' is the
          * starting point for substring instance.          *
          */
         if( (patternHash == textHash) &&
             (text.substr(i, pLen) == pattern) )
         {
            result.push_back(i);
         }

         /* For last iteration we don't want to calculate new hash values.
          * All the other iterations we do.
          */
         if( i< tLen-pLen)
         {
            textHash = reCalculateHash(textHash, text, i, i+pLen, pLen);
         }
      }
      return result;
   }
};

int main()
{
   rabinKarpSearch onj;
   vector<int> result = obj.matchPattern("hello", "hihelloworldhello");
   for( auto s : result)
   {
      cout << s << std::endl;
   }
   return 0;
}
