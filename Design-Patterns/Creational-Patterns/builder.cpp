/*
 *  Builder Design Pattern
 *
 *  Below is an example of Builder design pattern.
 *  We have defined "CarBuilder" abstract builder class and
 *  its goal is to provide interface to director("CarMaker")
 *  to construct Product("Car").
 *
 *  It hides how product gets assembled. It isolates construction
 *  and representation, by encapsulating the way complex object is
 *  built. this way we don't need constructors with long argument list
 *  and we can simple delegate the task of building to Builder.
 *
 *  Client code doesn't need to know anything about Product's internal
 *  state.
 */

#include<iostream>
#include<memory>
#include<string>

using namespace std;

/*
 * Car Class
 * This is the target product type that we are trying to build
 * with help of builder.
 *
 * Car is a complex class with multiple smaller components.
 */

class Car
{
public:
  void setEngine(string engine)
  {
    m_engineType = engine;
  }
  void setTransmission( string trType )
  {
    m_transmission = trType;
  }
  void setCapacity(int cap)
  {
    m_capacity = cap;
  }
  void display()
  {
    cout << " Car has " << m_engineType
         << " Engine With " << m_transmission
         << " And capacity " << m_capacity;
  }
  ~Car()
  {}
private:
  string m_engineType;
  string m_transmission;
  int m_capacity;
};

/*
 * Abstract Builder Class "CarBuilder"
 * In the builder, we want to build different components for Car.
 * Each component gets its own build method
 */

class CarBuilder
{
public:
  virtual void buildEngine() = 0;
  virtual void buildTransmission() = 0;
  virtual void buildCapacity() = 0;
  virtual ~CarBuilder()
  {}

  // Methods to create and retrieve Car
  void createCar()
  {
    m_car = make_unique<Car>();
  }
  unique_ptr<Car> retrieveCar()
  {
    return std::move(m_car);
  }

protected:
  unique_ptr<Car> m_car;
};

/*
 * Concrete Classes with implementation for CarBuilder
 */
class SportsCarBuilder : public CarBuilder
{
public:
  void buildEngine()
  {
    m_car->setEngine("V6");
  }
  void buildTransmission()
  {
    m_car->setTransmission("5-Speed Manual");
  }
  void buildCapacity()
  {
    m_car->setCapacity(2);
  }
  virtual ~SportsCarBuilder()
  {}
};

class FamilyCarBuilder : public CarBuilder
{
public:
  void buildEngine()
  {
    m_car->setEngine("V4");
  }
  void buildTransmission()
  {
    m_car->setTransmission("4-Speed Automatic");
  }
  void buildCapacity()
  {
    m_car->setCapacity(5);
  }
  virtual ~FamilyCarBuilder()
  {}
};

/*
 * Director Class "CarMaker".
 * CarMaker has a builder that it uses to build Car
 *
 */
class CarMaker
{
public:
  CarMaker( CarBuilder* bldrPtr ): m_builder( bldrPtr)
  {}

  void setbuilder( CarBuilder* bldrPtr )
  {
    m_builder = bldrPtr;
  }
  void buildCar()
  {
    m_builder->createCar();
    m_builder->buildEngine();
    m_builder->buildTransmission();
    m_builder->buildCapacity();
  }

  unique_ptr<Car> getCar()
  {
    return m_builder->retrieveCar();
  }
private:
  CarBuilder *m_builder;

};

/*
 * Client code
 */

int main()
{
  FamilyCarBuilder familyCarBldr;
  SportsCarBuilder sportsCarBldr;
  CarMaker cm(&familyCarBldr);


  cm.buildCar();
  unique_ptr<Car> fCar = cm.getCar();
  fCar->display();

  cout << endl;
  cm.setbuilder( &sportsCarBldr );
  cm.buildCar();
  unique_ptr<Car> sCar = cm.getCar();
  sCar->display();

  return 0;
}








