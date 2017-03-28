/*-----------------------------------------------------------------------------

 Observer Design Pattern

 Below is a simple example of Observer design pattern.
 Here we have 2 abstract classes : [1] Subject [2] Observer

 Subject  : It is responsible for subscribe, unsubscribe and notify observers.
 Observer : It observes Subject and after getting notified on state change,
            it also updates it's own state.

 Below is a simple stock price display application. Both subject and observer
 maintain a list of stock prices, once subject changes any stock price, observers
 will get notified and update their own stock prices as well.

 We have two observers here.
 [1] current Display : This shows current stock price.
 [2] Low-High Display : This shows min-max prices for stocks.

 Same way we can add "multiple display" versions that rely on stock price change.
 New observers can be dynamically added and removed.

------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::string;
using std::pair;
using std::make_pair;
using std::min;
using std::max;
// -----------------------------------------------------------------------------
/* 'Observer' abstract class. It includes "update" method that "subject" uses
 * to notify all observers.
 */
 class Observer
{
    public:
    virtual void update() = 0;
    virtual ~Observer() {}
};

/* 'Display' abstract class. This is just an additional functionality that observers
 * will have. It will use "display" method to display stock prices.
 */
class Display
{
    public:
    virtual void display() = 0;
    virtual ~Display() {}
};
// -----------------------------------------------------------------------------

/* 'Subject' abstract class. Subject supports subscribe, unsubscribe and notify methods to
 * deal with observers. In this context, it also supprots "getPrice" method, so observers
 * can pull stock price for a specific stock. This is to support "pull" behavior.
 */
class Subject
{
    public:
    virtual void subscribe( Observer* ) = 0;
    virtual void unsubscribe( Observer* ) = 0;
    virtual void notify() = 0;
    virtual int getPrice( string )= 0;
    virtual ~Subject() {}
};

// -----------------------------------------------------------------------------
/* This class displays current stock prices
 */
class CurrentDisplay : public Observer, public Display
{
    private:
    unordered_map<string, int> m_currentPrice;
    Subject *m_subPtr;

    public:

    CurrentDisplay( unordered_map<string, int>& stocks, Subject*  subPtr )
    {
        for( auto entry : stocks )
        {
            m_currentPrice[ entry.first ] = entry.second;
        }
        m_subPtr = subPtr;
    }
    void update()
    {
        for( auto entry : m_currentPrice )
        {
            m_currentPrice[ entry.first ] = m_subPtr->getPrice( entry.first );
        }
    }

    void display()
    {
        cout << "\n***** Current Stock Prices *****" << endl;
        for( auto entry : m_currentPrice )
        {
            cout << entry.first << " : " << entry.second << endl;
        }
    }
};

/* This class displays min-max price for all stocks
 */
class LowHighDisplay : public Observer, public Display
{
    private:
    unordered_map<string, pair<int,int>> m_lowHighPrice;
    Subject *m_subPtr;

    public:

    LowHighDisplay( unordered_map<string, int>& stocks, Subject*  subPtr )
    {
        for( auto entry : stocks )
        {
            m_lowHighPrice[ entry.first ] = make_pair(entry.second, entry.second);
        }
        m_subPtr = subPtr;
    }
    void update()
    {
        for( auto entry : m_lowHighPrice )
        {
            int newPrice = m_subPtr->getPrice( entry.first );
            int newLow = min( entry.second.first, newPrice);
            int newHigh = max( entry.second.second, newPrice);
            m_lowHighPrice[ entry.first ] = make_pair(newLow, newHigh);
        }
    }

    void display()
    {
        cout << "\n***** Low-High Stock Prices ***** " << endl;
        for( auto entry : m_lowHighPrice )
        {
            cout << entry.first << " : " << " Min = " << entry.second.first
            << " Max = "<< entry.second.second << endl;
        }
    }
};

// -----------------------------------------------------------------------------
/* This is the concrete class for "Subject". It manages stock prices and a list of
 * observers that subscribed to this Subject.
 */
class StockData : public Subject
{
    private:
    vector< Observer* > obsList;
    unordered_map< string, int> m_stockPrice;

    public:
    StockData( unordered_map<string, int> &stocks )
    {
        for( auto entry : stocks )
        {
            m_stockPrice[ entry.first ] = entry.second;
        }
    }

    void subscribe( Observer* obsPtr )
    {
        obsList.push_back( obsPtr );
        cout << "\nNew observer subscribed. Total Observers : " << obsList.size() << endl;
    }

    void unsubscribe( Observer* obsPtr )
    {
        int size = obsList.size();
        if( size == 0) return;
        int i;
        for(i=0; i<size; ++i)
        {
            if( obsList[i] == obsPtr ) break;
        }

        if( i< size ) obsList.erase( obsList.begin()+i);
        cout << "\nCurrent Observer un-subscribed. Total Observers : " << obsList.size() << endl;
    }

    void notify()
    {
        for( uint i =0; i<obsList.size(); ++i )
        {
            obsList[i]->update();
        }
    }

    void recordChanges( const string& name, const int& price )
    {
        // Change current price
        auto it = m_stockPrice.find(name);
        if( it != m_stockPrice.end() )
        {
            it->second = price;
        }

        // notify observers
        notify();
    }

    int getPrice( string name )
    {
        auto it = m_stockPrice.find(name);
        if( it != m_stockPrice.end() )
        {
            return it->second;
        }
        return -1;
    }

};

// -----------------------------------------------------------------------------
/* In Main, we create two observers and register it with single Subject. Any state
 * change to Subject will be published to Observers.
 */
int main()
{
    unordered_map< string, int> prices;
    prices["google"] = 100;
    prices["facebook"] = 80;

    StockData data(prices);
    CurrentDisplay currDis(prices, &data);
    LowHighDisplay lowHighDis(prices, &data);

    data.subscribe( &currDis );
    data.subscribe( &lowHighDis );

    currDis.display();
    lowHighDis.display();

    data.recordChanges("google", 150);
    data.recordChanges("facebook", 120);

    currDis.display();
    lowHighDis.display();

    data.unsubscribe( &currDis);

    return 0;
}
