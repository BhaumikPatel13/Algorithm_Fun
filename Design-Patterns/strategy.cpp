/*-----------------------------------------------------------------------------

 Strategy Design Pattern

 Below is a simple example of Strategy design pattern.

 Here we have 2 abstract classes : [1] SortData [2] SaveData
 Both represents family of algorithms that can be encapsulated in client code and
 used interchangeable at run-time.

------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// -----------------------------------------------------------------------------
// Abstract class for Sort algorithms
class SortData
{
    public:
    virtual void sort(vector<int>& data) const = 0;
    virtual ~SortData() {}
};

// Below are three concrete classes that implements SortData

class MergeSort : public SortData
{
    public:
    void sort( vector<int>& data ) const
    {
        cout << "Sorting using Merge Sort " << endl;
    }
};

class QuickSort : public SortData
{
    public:
    void sort( vector<int>& data ) const
    {
        cout << "Sorting using Quick Sort " << endl;
    }
};

class BubbleSort : public SortData
{
    public:
    void sort( vector<int>& data ) const
    {
        cout << "Sorting using Bubble Sort " << endl;
    }
};

// -----------------------------------------------------------------------------
// Abstract class for Save algorithms
class SaveData
{
    public:
    virtual void save( vector<int>& data ) const = 0;
    virtual ~SaveData() {}
};

// Below are two concrete classes that implements SaveData

class FileSave : public SaveData
{
    public:
    void save( vector<int>& data ) const
    {
        cout << "Saving Data in File " << endl;
    }
};

class DataBaseSave : public SaveData
{
    public:
    void save( vector<int>& data ) const
    {
        cout << "Saving Data in Database " << endl;
    }
};

// -----------------------------------------------------------------------------

/* Client class to manage client code. Here we can easily change our algorithms at
 * run time. Client only knows about the abstract class and expects sort() and save()
 * methods to be implemented by concrete class.
 */

class Client
{
    private:
    SortData *m_sortPtr;
    SaveData *m_savePtr;

    public:
    Client()
    {}

    void setSortingAlgo( SortData* ptr )
    {
        m_sortPtr = ptr;
    }

    void setSavingAlgo( SaveData* ptr)
    {
        m_savePtr = ptr;
    }

    void manageData( vector<int>& data)
    {
        m_sortPtr->sort( data );
        m_savePtr->save( data );
    }
};


int main()
{
    Client myClient;
    vector<int> data = {1,2,3,4};

    myClient.setSortingAlgo( new MergeSort() );
    myClient.setSavingAlgo( new DataBaseSave() );
    myClient.manageData( data );

    cout << "\n****** Changing algorithms ******\n" <<  endl;

    myClient.setSortingAlgo( new BubbleSort() );
    myClient.setSavingAlgo( new FileSave() );
    myClient.manageData( data );

    return 0;
}
