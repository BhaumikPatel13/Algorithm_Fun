/*
 *  Protection Proxy Design Pattern
 *
 *  This pattern is used to control access to real object.
 *  Protection proxy acts as placeholder to actual object
 *  and performs permission checks.
 *
 */

#include<iostream>
#include<string>
#include<set>
#include<vector>

using namespace std;

/*
 * Abstract Subject class "fileHandling"
 */
class fileHandling
{
public:
  virtual void accessFile( string fileName ) = 0;
  virtual ~fileHandling()
  {}
};

/*
 * Real subject class "fileWritter"
 */
class fileWritter : public fileHandling
{
public:
  void accessFile( string fileName )
  {
    cout << "Accessing "<< fileName << " file" << endl;
  }
  ~fileWritter()
  {}
};

/*
 * Proxy class "fileWrapper"
 * This class is a surrogate for "fileWritter" class.
 * It performs permission checks befor allowing user
 * to access the realobject.
 *
 */
class fileWrapper : public fileHandling
{
public:
  fileWrapper() : m_fileWriter()
  {
    userList.insert("user1");
    userList.insert("user2");
    userList.insert("admin");
  }
  bool tryAccessing( string user, string fileName )
  {
    if( userList.find(user) != userList.end() )
    {
      accessFile( fileName );
      return true;
    }
    else
    {
      return false;
    }
  }

  void accessFile( string fileName )
  {
    m_fileWriter.accessFile( fileName );
  }
  ~fileWrapper()
  {}

private:
  fileWritter m_fileWriter;
  set<string> userList;
};

/*
 * Client code.
 */
int main()
{
  vector<string> userNames = { "user1", "user3", "admin", "user4", "user2" };
  fileWrapper fw;

  for(size_t i=0; i<userNames.size(); ++i)
  {
    bool isAllowed = fw.tryAccessing( userNames[i], "sample.txt");
    if( !isAllowed )
    {
      cout << userNames[i] << " is not allowed" << endl;
    }

  }

  return 0;
}

