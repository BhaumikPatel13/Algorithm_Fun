/*----------------------------------------------------------------------
[1] Basic Binary Search

	Given a sorted array and target , find the index of first occurance
	of target in array.

----------------------------------------------------------------------*/
#include<iostream>
#include<vector>

using std::vector;
using std::cout;

int binarySearch( const vector<int>& input, const int& target )
{
	int lo = 0;
	int hi = input.size();
	int result = -1;

	while( lo <= hi )
	{
		int mid = lo + ( hi - lo )/2;
		if( input[mid] == target )
		{
			result = mid;
			hi = mid - 1;
		}
		else if( input[mid] > target )
		{
			hi = mid - 1;
		}
		else
		{
			lo = mid +1;
		}
	}

	return result;
}
// addding comment at the end
