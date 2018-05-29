#include <iostream>

using namespace std;

class punto
{
private:
  double x,y;
public:
  punto(double xx, double yy) : x(xx), y(yy) {};
  double getX() {return x;}
  double getY() {return y;}
  void setX(double xx) {x=xx;}
  void setY(double yy) {y=yy;}
  punto operator+(const punto& b);
  punto operator+=(const punto& b);
  punto& operator++(); //++p
  punto operator++(int); //++p
};

punto punto::operator+(const punto& b)
{
  punto temp(0.0,0.0);

  temp.x=this->x+b.x;
  temp.y=this->y+b.y;

  return temp;
}
