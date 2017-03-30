/*-----------------------------------------------------------------------------

 Decorator Design Pattern

 Below is a simple example of Decorator design pattern.

 [1] "Beverage" is an abstract class with "Espresso" and "Mocha" begin concrete
      implementation.
 [2] "Decorator" inherits "Beverage" and holds a pointer of type Beverage.
 [3] "Mocha" and "Whip" inherits decorator and provides additional responsibility.

 Using decorator pattern, we can attach additional responsibility to an object
 dynamically. Here we use "Mocha" and "Whip" to decorate Beverage.

 This is a flexible alternative to subclassing for extending functionality. For example,
 Same behavior can be achieved by making additional classes like, EspressoMocha, EspressoWhip,
 DecafMochWhip, DecafWhip etc.

------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*------------------------------------------------------------------------------
 * Abstract Beverage class
 */
class Beverage
{
public:
   virtual string getDescription() = 0;
   virtual double getCost() = 0;
   virtual ~Beverage(){}
};

/*------------------------------------------------------------------------------
 * Concrete classes inheriting Beverage
 */
class Espresso: public Beverage
{
private:
   const double m_cost = 2;
public:
   Espresso( )
   { }

   string getDescription()
   {
      return " Espresso ";
   }

   double  getCost()
   {
      return m_cost;
   }
};

class Decaf: public Beverage
{
private:
   const double m_cost = 1.90;
public:
   Decaf()
   { }

   string getDescription()
   {
      return " Decaf ";
   }

   double  getCost()
   {
      return m_cost;
   }
};

/*------------------------------------------------------------------------------
 * Decorator class that inherits Beverage.
 * One things to notice here is, Decorator class hold a "pointer of type Beverage".
 * Client is responsible for passing a pointer to "concrete" Beverage class that
 * we will decorate.
 */

class Decorator : public Beverage
{
private:
   Beverage* m_beveragePtr;
public:
   Decorator( Beverage* ptr ) : m_beveragePtr(ptr)
   { }

   string getDescription()
   {
      return m_beveragePtr->getDescription();
   }

   double getCost()
   {
      return m_beveragePtr->getCost();
   }
};

/*------------------------------------------------------------------------------
 * Additional condiments classes that inherit Decorator.
 * These classes will be used to provide additional functionality to concrete class.
 */
class Mocha : public Decorator
{
public:
   Mocha( Beverage* ptr ) : Decorator( ptr )
   { }

   string getDescription()
   {
      return Decorator::getDescription() + " with Mocha";
   }

   double getCost()
   {
      return Decorator::getCost() + 0.30 ;
   }
};

class Whip : public Decorator
{
public:
   Whip( Beverage* ptr ) : Decorator( ptr )
   { }

   string getDescription()
   {
      return Decorator::getDescription() + " with Whip";
   }

   double getCost()
   {
      return Decorator::getCost() + 0.40 ;
   }
};

/* ------------------------------------------------------------------------------
 * Main has different beverages with different condiments.
 */

int main()
{
   Beverage* bevPtr1 = new Whip( new Espresso() );
   cout << bevPtr1->getDescription() << endl;
   cout << " Cost is : $" << bevPtr1->getCost();

   cout << "\n *************** " << endl;

   Beverage* bevPtr2 = new Mocha( new Whip( new Decaf()) );
   cout << bevPtr2->getDescription() << endl;
   cout << " Cost is : $" << bevPtr2->getCost();

   return 0;
}
