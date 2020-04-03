#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <string>

using namespace std;

class C
{
private:
  float x;

public:
  C(float _x) : x(_x) {};
  virtual double f() = 0;
  float getX() {return x};

  virtual ostream &put(ostream &os) const
  {
    return os << "Class " << typeid(*this).name() << ": x = " << x << " ";
  }
};

ostream &operator <<(ostream &left, const A obj)
{
  return obj.put(left);
}
class A
{
protected:
  C* obj1;
  C* obj2;

public:
  A(float x)
  {
    obj1 = new D(_x);
    obj2  = new E(_x);
  }
};
