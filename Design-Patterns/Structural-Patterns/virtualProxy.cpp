/*
 *  Virtual Proxy Design Pattern
 *
 *  This pattern is used for lazy initialization.
 *  In below example, "proxyImage" lazily initializes
 *  "realImage" only when needed. It act like a placeholdder
 *  to hold real image.
 *
 */

#include<iostream>
#include<string>

using namespace std;

/*
 * Abstract Subject class "Image"
 */
class Image
{
public:
  virtual void draw() = 0;
  virtual ~Image()
  {}
};

/*
 * Real subject class "realImage"
 */
class realImage : public Image
{
public:
  void draw()
  {
    cout << " Drawing Real Image " << endl;
  }
  ~realImage()
  {}

};

/*
 * Proxy class "proxyImage"
 * This class is a surrogate for "realImage" class.
 * "draw()" method lazily initializes realImage and delegates
 * "drawing" responsibility to real image
 *
 */
class proxyImage : public Image
{
public:
  proxyImage() : m_realImagePtr(nullptr)
  {}

  void draw()
  {
    if( !m_realImagePtr )
    {
      m_realImagePtr = new realImage();
    }
    m_realImagePtr->draw();
  }
  ~proxyImage()
  {
    delete m_realImagePtr;
  }

private:
  realImage* m_realImagePtr;
};

/*
 * Client code.
 */
int main()
{
  proxyImage images[10];
  int i=0;
  while(i<10)
  {
    ++i;
    int random = rand()%10;
    cout << " Image # " << random << " ";
    images[random].draw();
  }
  return 0;
}

