/*-----------------------------------------------------------------------------

 Factory Method Design Pattern

 Below is a simple example of Factory Method design pattern.

 [1] "Pizza" is an abstract class, inherited by NYCheese, NYVeggie, ChicagoCheese,
     and ChicagoVeggie concrete sub-classes. they all provide valid implementation
     for "bake" and "cut" methods.
 [2] "PizzaStore" is a base class for specific store, which provides method to "order"
     a pizza but it relies on derived classes to "create"a pizza.
 [3] NYPizzaStore and ChicagoPizzaStore are classes that inherits PizzaStore and
     provide implementation for "createPizza" method.

 Here "createPizza" is a factory method. PizzaStore defines an interface for creating
 objects, but it lets sub-class decide which concrete class object to instantiate.

 Client knows about abstract class "Pizza", but it doesn't know  about any concrete
 Pizza classes. So it asks Factory Method to instantiate concrete Pizza class at run time.

------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*------------------------------------------------------------------------------
 * Abstract Pizza class
 */

class Pizza
{
public:
   virtual void bake() = 0;
   virtual void cut() = 0;
   virtual string getDescription() = 0;
   virtual ~Pizza(){}
};

/*------------------------------------------------------------------------------
 * Concrete Pizza class implementation
 */

class NYCheese : public Pizza
{
public:
   void bake()
   {
      cout << "Baking NY Cheese Pizza : 20 mins" << endl;
   }
   void cut()
   {
      cout << "Cutting  square slices " << endl;
   }
   string getDescription()
   {
      return string("NY style Cheese Pizza");
   }
};

class NYVeggie : public Pizza
{
public:
   void bake()
   {
      cout << "Baking NY Veggie Pizza : 25 mins " << endl;
   }
   void cut()
   {
      cout << "Cutting  square slices " << endl;
   }
   string getDescription()
   {
      return string("NY style Veggie Pizza");
   }
};

class ChicagoCheese : public Pizza
{
public:
   void bake()
   {
      cout << "Baking Chicago Cheese Pizza : 18 mins" << endl;
   }
   void cut()
   {
      cout << "Cutting  diagonal slices " << endl;
   }
   string getDescription()
   {
      return string("Chicago style Cheese Pizza");
   }
};

class ChicagoVeggie : public Pizza
{
public:
   void bake()
   {
      cout << "Baking Chicago Veggie Pizza : 22 mins" << endl;
   }
   void cut()
   {
      cout << "Cutting  diagonal slices " << endl;
   }
   string getDescription()
   {
      return string("Chicago style Veggie Pizza");
   }
};

/*------------------------------------------------------------------------------
 * Base class for "PizzaStore"
 */
class PizzaStore
{
public:
   virtual Pizza* createPizza( string pizzaName ) = 0;
   Pizza* orderPizza(string pizzaName )
   {
      Pizza* pizzaPtr = createPizza( pizzaName );
      pizzaPtr->bake();
      pizzaPtr->cut();
      return pizzaPtr;
   }
   virtual ~PizzaStore() {}
};

/*------------------------------------------------------------------------------
 * concrete sub-classes inherits PizzaStore and implements "createPizza" factory method.
 * Sub-class decides which concrete Pizza to instantiate. "OorderPizza" method from base
 * class will be common for both derived classes.
 */
class NYPizzaStore : public PizzaStore
{
public:
   Pizza* createPizza( string name )
   {
      Pizza* pizzaPtr = nullptr;
      if( name == "cheese" )
      {
         pizzaPtr = new NYCheese();
      }
      else if( name == "veggie" )
      {
         pizzaPtr = new NYVeggie();
      }
      return pizzaPtr;
   }
};

class ChicagoPizzaStore : public PizzaStore
{
public:
   Pizza* createPizza( string name )
   {
      Pizza* pizzaPtr = nullptr;
      if( name == "cheese" )
      {
         pizzaPtr = new ChicagoCheese();
      }
      else if( name == "veggie" )
      {
         pizzaPtr = new ChicagoVeggie();
      }
      return pizzaPtr;
   }
};

/*------------------------------------------------------------------------------
 * Client code
 */
int main()
{
   PizzaStore* nyStore = new NYPizzaStore();
   PizzaStore* chStore = new ChicagoPizzaStore();

   Pizza* nyVeggiePtr = nyStore->orderPizza("veggie");
   cout << "Ordered a " << nyVeggiePtr->getDescription() << endl;

   cout << "\n*****    *****\n";

   Pizza* chCheesePtr = chStore->orderPizza("cheese");
   cout << "Ordered a " << chCheesePtr->getDescription() << endl;

   return 0;
}
