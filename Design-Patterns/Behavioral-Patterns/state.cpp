
/*
 *  Garage Door state machine using "State Design Patter"
 *
 *  In state design pattern, we implement each state as class.
 *
 *  For Garage Door, we will consider below states.
 *
 *  [1] open
 *  [2] closed
 *  [3] Opening
 *  [4] closing
 *
 *  State transition will be triggered by below events.
 *  [1] pushButton : Manually pushed button to open-close door.
 *  [2] MotorStall : When motor hits stall and no longer continue.
 *                   This will occur on a complete open and complete close
 *  [3] sensorTrip : While closing if sensor detects a blocking object
 *
 *  State TRansitions are as per follow.
 *
 *  [1] Close   --> [ PushButton ] --> Opening
 *  [2] Opening --> [ MotorStall ] --> Open
 *  [3] Opening --> [ PushButton ] --> Closing
 *  [4] Open    --> [ PushButton ] --> Closing
 *  [5] Closing --> [ PushButton ] --> Opening
 *  [6] Closing --> [ SensorTrip ] --> Opening
 *  [7] Closing --> [ MotorStall ] --> Close
 *
 */

#include<iostream>
#include <string>
#include <functional>
#include <vector>

using namespace std;

class StateMachine
{
  class State* currentState;

public:
  StateMachine();
  void setState(State* newState);
  void pushButton();
  void motorStall();
  void sensorTrip();
};

/*
 * Abstract State class and pure virtual methods for all events.
 */

class State
{
public:
  State()
  {}
  virtual void pushButton( StateMachine* m ) = 0;
  virtual void motorStall( StateMachine* m ) = 0;
  virtual void sensorTrip( StateMachine* m ) = 0;
  virtual ~State()
  {}
};

/*
 * Concrete classes inherited from State.
 * These classes represent States for our Garage door.
 */
class open : public State
{
public:
  open()
  {}
  void pushButton( StateMachine* m );
  void motorStall( StateMachine* m );
  void sensorTrip( StateMachine* m );
  ~open()
  {}
};

class close : public State
{
public:
  close()
  {}
  void pushButton( StateMachine* m );
  void motorStall( StateMachine* m );
  void sensorTrip( StateMachine* m );
  ~close()
  {}
};

class opening : public State
{
public:
  opening()
  {}
  void pushButton( StateMachine* m );
  void motorStall( StateMachine* m );
  void sensorTrip( StateMachine* m );
  ~opening()
  {}
};

class closing : public State
{
public:
  closing()
  {}
  void pushButton( StateMachine* m );
  void motorStall( StateMachine* m );
  void sensorTrip( StateMachine* m );
  ~closing()
  {}
};


/*
 * Concrete Classes member function implementation. Methods with
 * empty body represents state transition that are not supported
 * at the moment. So in those cases, we dont perform state transition.
 */
void open::pushButton( StateMachine* m )
{
  cout << "Going from OPEN --> CLOSING on PUSHBUTTON EVENT " << endl;
  m->setState(new closing());
  delete this;

}
void open::motorStall( StateMachine* m )
{}
void open::sensorTrip( StateMachine* m )
{}


void close::pushButton( StateMachine* m )
{
  cout << "Going from CLOSE --> OPENING on PUSHBUTTON EVENT " << endl;
  m->setState(new opening());
  delete this;
}
void close::motorStall( StateMachine* m )
{}
void close::sensorTrip( StateMachine* m )
{}


void opening::pushButton( StateMachine* m )
{
  cout << "Going from OPENING --> CLOSING on PUSHBUTTON EVENT " << endl;
  m->setState(new closing());
  delete this;
}
void opening::motorStall( StateMachine* m )
{
  cout << "Going from OPENING --> OPEN on MOTORSTALL EVENT " << endl;
  m->setState(new open());
  delete this;
}
void opening::sensorTrip( StateMachine* m )
{}


void closing::pushButton( StateMachine* m )
{
  cout << "Going from CLOSING --> OPENING on PUSHBUTTON EVENT " << endl;
  m->setState(new opening());
  delete this;
}
void closing::motorStall( StateMachine* m )
{
  cout << "Going from CLOSING --> CLOSE on MOTORSTALL EVENT " << endl;
  m->setState(new close());
  delete this;
}
void closing::sensorTrip( StateMachine* m )
{
  cout << "Going from CLOSING --> OPENING on SENSORTRIP EVENT " << endl;
  m->setState(new opening());
  delete this;
}
/*
 * StateMachine public methods implementation
 */
StateMachine::StateMachine()
{
  currentState = new close();
}
void StateMachine::setState(State* newState)
{
  currentState = newState;
}
void StateMachine::pushButton()
{
  currentState->pushButton(this);
}
void StateMachine::motorStall()
{
  currentState->motorStall(this);
}
void StateMachine::sensorTrip()
{
  currentState->sensorTrip(this);
}

/*
 * Main
 */

int main()
{
  StateMachine sm;

 vector< function<void()> > callable = { bind( &StateMachine::pushButton, &sm ),
                                         bind( &StateMachine::motorStall, &sm ),
                                         bind( &StateMachine::sensorTrip, &sm) };
  int n;
  while(1)
  {
    cout << " input 0-Push/1-Motor/2-Sensor OR 9 for quit " << endl;
    cin >> n;
    if(n == 9 ) break;

    callable[n]();
  }
  return 0;
}
